#include "Note.h"

Note::Note(std::string t, std::string cl, std::string c)
    : id(generate_id()), title(std::move(t)), color(cl), content(std::move(c)), createdAt(std::chrono::system_clock::now()), modifiedAt(createdAt){}


