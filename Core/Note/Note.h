#ifndef NOTE_H
#define NOTE_H

#include <string>
#include <chrono>
#include <QUuid>

struct Note
{    
    std::string id;
    std::string title;
    std::string color;
    std::string content;
    std::chrono::system_clock::time_point createdAt;
    std::chrono::system_clock::time_point modifiedAt;

    Note(std::string t = {}, std::string cl = {}, std::string c = {});

    // move-semanic
    Note(Note&&) noexcept = default;
    Note& operator=(Note&&) noexcept = default; // moving data instead of copying

    inline std::string generate_id() {
        return QUuid::createUuid().toString(QUuid::WithoutBraces).toStdString();
    }
};

#endif // NOTE_H
