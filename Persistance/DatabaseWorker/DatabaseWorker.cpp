#include "DatabaseWorker.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <QDateTime>

DatabaseWorker::DatabaseWorker(const QString& connectionName)
{
    if (QSqlDatabase::contains(connectionName)) {
        QSqlDatabase::removeDatabase(connectionName);
    }

    m_db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    m_db.setDatabaseName("data.db");

    if (!m_db.open()) {
        qDebug() << "DB open error:" << m_db.lastError().text();
    }
}

bool DatabaseWorker::addNote(const Note& note) {
    if (!m_db.isOpen()) {
        qDebug() << "DB not open in addNote()";
        return false;
    }

    QSqlQuery query(m_db);
    query.prepare("INSERT INTO notes (id, title, content, created_at, modified_at) VALUES (?,?,?, datetime('now'), datetime('now'))");

    qDebug() << "id in db: " << note.id;

    query.addBindValue(QString::fromStdString(note.id));
    query.addBindValue(QString::fromStdString(note.title));
    query.addBindValue(QString::fromStdString(note.content));

    if (!query.exec()) {
        qDebug() << "Insert in db failed: " << query.lastError().text();
        return false;
    }

    return true;
}

std::vector<Note> DatabaseWorker::getAllNotes() {
    std::vector<Note> notes;
    QSqlQuery query(m_db);
    query.exec("SELECT id, title, content FROM notes");

    while (query.next()) {
        Note note(
            query.value(1).toString().toStdString(),
            query.value(2).toString().toStdString()
        );
        note.id = query.value(0).toString().toStdString();
        notes.push_back(std::move(note));
    }

    return notes;
}

bool DatabaseWorker::updateNote(const Note& note) {
    QSqlQuery query(m_db);
    query.prepare("UPDATE notes SET title = :title, content = :content, modified_at = :modified_at WHERE id = :id");

    query.bindValue(":title", QString::fromStdString(note.title));
    query.bindValue(":content", QString::fromStdString(note.content));

    QString modfiedTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    query.bindValue(":modified_at", modfiedTime);
    query.bindValue(":id", QString::fromStdString(note.id));

    if (!query.exec()) {
        qDebug() << "Update failed: " << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseWorker::removeNote(const std::string& id) {
    QSqlQuery query(m_db);
    query.prepare("DELETE FROM notes WHERE id = :id");

    query.bindValue(":id", QString::fromStdString(id));

    if (!query.exec()) {
        qDebug() << "Remove failed: " << query.lastError().text();
        return false;
    }

    return true;
}

std::optional<Note> DatabaseWorker::getNoteById(const std::string& id) {
    QSqlQuery query(m_db);
    query.prepare("SELECT id, title, content, FROM notes WHERE id = :id");

    query.bindValue(":id", QString::fromStdString(id));

    if (!query.exec()) {
        qDebug() << "Remove failed: " << query.lastError().text();
        return std::nullopt;
    }

    if (query.next()) {
        Note note(
            query.value(1).toString().toStdString(),
            query.value(2).toString().toStdString()
        );
        note.id = query.value(0).toString().toStdString();
        return note;
    }

    return std::nullopt;
}
