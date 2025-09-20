#ifndef NOTESLIST_H
#define NOTESLIST_H

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>

#include "../../Persistance/DatabaseWorker/DatabaseWorker.h"

class NotesList : public QListWidget
{
    Q_OBJECT
public:
    explicit NotesList(QWidget* parent = nullptr);

};

#endif // NOTESLIST_H
