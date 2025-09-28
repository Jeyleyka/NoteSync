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

void NotesList::addNote(const QString& id, const QColor &color, const QString &text) {
    auto* note = new NoteUI(id, color, text, this);
    notes.push_back(note);

    layout->insertWidget(layout->count() - 1, note);
}

void NotesList::loadNotes() {
    DatabaseWorker dbWorker;

    for (auto& c : dbWorker.getAllNotes()) {
        auto* note = new NoteUI(QString::fromStdString(c.id), QColor(QString::fromStdString(c.color)), QString::fromStdString(c.title), this);
        connect(note, &NoteUI::saveChanges, this, &NotesList::onSaveNoteChanges);

        notes.push_back(note);
        layout->insertWidget(layout->count() - 1, note);
    }

    for (auto* note : notes) {
        connect(note, &NoteUI::editingStarted, this, [this](NoteUI* note) {
            if (editingNote == nullptr) {
                editingNote = note;
                // включаем редактирование у этой карточки
                note->startEditing();

                // блокируем кнопки у всех остальных
                for (auto* n : notes) {
                    if (n != note) {
                        n->setEditEnabled(false);
                    }
                }
            } else if (editingNote != note) {
                // кто-то уже редактируется → игнорируем
            }
        });

        connect(note, &NoteUI::editingFinished, this, [this](NoteUI* note) {
            if (editingNote == note) {
                editingNote = nullptr;
                // разблокируем все кнопки
                for (auto* n : notes) {
                    n->setEditEnabled(true);
                }
            }
        });
    }
}
