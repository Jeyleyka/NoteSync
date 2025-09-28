#ifndef NOTESLIST_H
#define NOTESLIST_H

#include <QWidget>
#include <QVector>
#include <QVBoxLayout>

#include "../NoteUI/NoteUI.h"

#include "../../Persistance/DatabaseWorker/DatabaseWorker.h"

class NotesList : public QWidget
{
    Q_OBJECT
public:
    explicit NotesList(QWidget* parent = nullptr);

    void addNote(const QString& id, const QColor& color, const QString& text);
    void loadNotes();

signals:
    void onSaveNoteChanges(NoteUI& note);
    void onShowInterface(const QString& id, const QColor& color, const QString& title);

private:
    NoteUI* editingNote = nullptr;

    QVBoxLayout* layout;

    QVector<NoteUI*> notes;
};

#endif // NOTESLIST_H
