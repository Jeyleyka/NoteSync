#include "NoteManager.h"

#include "../Note/Note.h"

NoteManager::NoteManager() {}

const Note& NoteManager::add(const std::string& title, const std::string& color, const std::string& content) {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto newNote = std::make_unique<Note>(title, color, content);
    auto id = newNote->id;
    this->notes.emplace(id, std::move(newNote));
    return *this->notes.at(id);
}

bool NoteManager::remove(const std::string& id) {
    std::lock_guard<std::mutex> lock(m_mutex);
    return this->notes.erase(id) > 0;
}

bool NoteManager::update(const std::string& id, const std::string& newTitle, const std::string& newColor, const std::string& newContent) {
    std::lock_guard<std::mutex> lock(m_mutex);

    auto it = this->notes.find(id);

    if (it == this->notes.end()) {
        qDebug() << "note not updated\n";
        return false;
    }

    auto& note = it->second;
    note->title = newTitle;
    note->color = newColor;
    note->content = newContent;
    return true;
}

std::vector<std::reference_wrapper<Note>> NoteManager::getAll() {
    std::lock_guard<std::mutex> lock(m_mutex);
    std::vector<std::reference_wrapper<Note>> res;
    res.reserve(this->notes.size());

    for (auto& [id, note] : this->notes)
        res.push_back(*note);

    return res;
}

std::optional<std::reference_wrapper<const Note>> NoteManager::getNote(const std::string& id) {
    auto it = this->notes.find(id);
    if (it == this->notes.end()) return std::nullopt;
    return *it->second;
}
