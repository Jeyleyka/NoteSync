#include "NotesList.h"

NotesList::NotesList(QWidget* parent)
    : QListWidget(parent)
{
    addItem("Meeting notes - 15 Sep");
    addItem("Shopping list");
    addItem("Project ideas");
}
