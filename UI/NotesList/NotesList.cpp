#include "NotesList.h"

NotesList::NotesList(QWidget* parent)
    : QListWidget(parent)
{
    Database& db = Database::instance();
    DatabaseWorker dbWorker(db);

    for (auto& c : dbWorker.getAllNotes()) {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(c.title));
        item->setData(Qt::UserRole, QString::fromStdString(c.id));
        addItem(item);
    }
}
