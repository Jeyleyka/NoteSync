#include "NotesList.h"

#include <QVBoxLayout>

NotesList::NotesList(QWidget* parent)
    : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(10);
    layout->addStretch();
}

void NotesList::addNote(const QColor &color, const QString &text) {
    auto* note = new NoteUI(color, text, this);
    notes.push_back(note);

    layout->insertWidget(layout->count() - 1, note);
}

void NotesList::loadNotes() {
    DatabaseWorker dbWorker;

    for (auto& c : dbWorker.getAllNotes()) {
        auto* note = new NoteUI(QColor(QString::fromStdString(c.color)), QString::fromStdString(c.title), this);
        notes.push_back(note);
        layout->insertWidget(layout->count() - 1, note);
    }
}
