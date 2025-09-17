#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

#include "../../Core/Note/Note.h"

class Database
{
public:
    static Database& instance();

    bool isOpen() const;
    QSqlDatabase database() const;
    bool init();

private:
    Database();
    ~Database();

    QSqlDatabase m_db;
};

#endif // DATABASE_H
