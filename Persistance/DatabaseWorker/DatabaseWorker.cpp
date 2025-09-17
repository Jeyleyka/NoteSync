#include "DatabaseWorker.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

DatabaseWorker::DatabaseWorker(Database& database) : db(database) {}

bool DatabaseWorker::addNote(const Note& note) {
    QSqlQuery query;
    query.prepare("INSERT INTO notes (id, title, content, created_at, modified_at) VALUES (?,?,?, datetime('now'), datetime('now'))");

    query.addBindValue(QString::fromStdString(note.id));
    query.addBindValue(QString::fromStdString(note.title));
    query.addBindValue(QString::fromStdString(note.content));

    if (!query.exec()) {
        qDebug() << "Insert failed: " << query.lastError().text();
        return false;
    }

    return true;
}
