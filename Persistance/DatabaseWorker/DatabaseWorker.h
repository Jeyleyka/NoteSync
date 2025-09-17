#ifndef DATABASEWORKER_H
#define DATABASEWORKER_H

#include <string>
#include <vector>
#include <optional>
#include <QSqlDatabase>

#include "../../Core/Note/Note.h"
#include "../Database/Database.h"

class DatabaseWorker
{
public:
    explicit DatabaseWorker(Database& database);

    bool addNote(const Note& note);
    std::vector<Note> getAllNotes();
    bool updateNote(const Note& note);
    bool removeNote(const std::string& id);
    std::optional<Note> getNoteById(const std::string& id);

private:
    Database& db;
};

#endif // DATABASEWORKER_H
