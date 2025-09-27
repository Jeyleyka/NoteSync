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

    void addNote(const QColor& color, const QString& text);
    void loadNotes();
    // void clearNotes();

private:
    QVBoxLayout* layout;
    QVector<NoteUI*> notes;
};

#endif // NOTESLIST_H
