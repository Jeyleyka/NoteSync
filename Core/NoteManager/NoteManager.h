#ifndef NOTEMANAGER_H
#define NOTEMANAGER_H

#include <memory>
#include <unordered_map>
#include <optional>
#include <list>
#include <qDebug>
#include <mutex>

class Note;

class NoteManager
{
public:
    NoteManager();

    const Note& add(const std::string& title, const std::string& content);
    bool remove(const std::string& id);
    bool update(const std::string& id, const std::string& newTitle, const std::string& newContent);
    std::vector<std::reference_wrapper<Note>> getAll();
    std::optional<std::reference_wrapper<const Note>> getNote(const std::string& id);

private:
    std::unordered_map<std::string, std::unique_ptr<Note>> notes;
    mutable std::mutex m_mutex;
};

#endif // NOTEMANAGER_H
