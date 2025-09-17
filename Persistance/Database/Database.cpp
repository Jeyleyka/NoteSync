#include "Database.h"

Database::Database() {
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("data.db");

    if (!m_db.open())
        qDebug() << "Open db failed: " << m_db.lastError().text();
    else
        qDebug() << "Db opened successfully";
}

Database::~Database() {
    if (m_db.isOpen())
        m_db.close();
}

Database& Database::instance() {
    static Database singleton;
    return singleton;
}

bool Database::isOpen() const {
    return m_db.isOpen();
}

QSqlDatabase Database::database() const {
    return m_db;
}

bool Database::init() {
    if (!m_db.isOpen())  {
        qDebug() << "db not open\n";
        return false;
    }

    QSqlQuery query;


    QString sql = R"(
        CREATE TABLE IF NOT EXISTS notes (
            id TEXT NOT NULL,
            title TEXT,
            content TEXT,
            created_at TEXT,
            modified_at TEXT
        )
    )";

    if (!query.exec(sql)) {
        qDebug() << "create table failed: " << query.lastError().text();
        return false;
    }

    return true;
}

bool Database::insertNoteInDB(const QString& id, const QString& title, const QString& content) {
    QSqlQuery query;
    query.prepare("INSERT INTO notes (id, title, content, created_at, modified_at) VALUES (?,?,?, datetime('now'), datetime('now'))");

    query.addBindValue(id);
    query.addBindValue(title);
    query.addBindValue(content);

    if (!query.exec()) {
        qDebug() << "Insert failed: " << query.lastError().text();
        return false;
    }

    return true;
}
