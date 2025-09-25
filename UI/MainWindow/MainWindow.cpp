#include "MainWindow.h"
#include <QMainWindow>
#include <QSplitter>
#include <thread>

#include "../NoteUI/NoteUI.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    Database& db = Database::instance();

    if (!db.isOpen()) {
        qDebug() << "Не удалось открыть БД!";
        return;
    }

    db.init();

    this->setWindowTitle("NoteSync");
    this->resize(1200, 700);

    // === Toolbar ===
    this->header = new Header(this);
    this->addToolBar(header->getToolBar());


    // === Sidebar (categories) ===
    this->catList = new CategoriesList(this);

    NoteUI* note = new NoteUI(QColor("#7F5F01"), "some", this);

    // === Center (list of notes) ===
    this->noteList = new NotesList(this);

    connect(this->noteList, &NotesList::itemDoubleClicked, this, [this](QListWidgetItem* item) {
        this->editor->setText(item->text());
        std::string id = item->data(Qt::UserRole).toString().toStdString();

        qDebug() << "current id: " << id;
    });

    // === Right (editor) ===
    this->editor = new Editor(this);

    connect(this->header, &Header::onRemoveNote, this, [this] {
        std::thread([this] {
            DatabaseWorker dbWorker;

            QListWidgetItem* currentItem = this->noteList->currentItem();

            if (currentItem) {
                const QString qid = currentItem->data(Qt::UserRole).toString();
                if (qid.isEmpty()) {
                    qDebug() << "No id stored in item!";
                    return;
                }
                const std::string noteId = qid.toStdString();

                this->noteManager.remove(noteId);
                dbWorker.removeNote(noteId);

                QMetaObject::invokeMethod(this, [this, currentItem] {
                    delete this->noteList->takeItem(this->noteList->row(currentItem));
                }, Qt::QueuedConnection);

            } else
                qDebug() << "invalid item";

        }).detach();
    });

    connect(this->header, &Header::onAddNote, this, [this] {

        std::string content = this->editor->toPlainText().toStdString();

        QStringList lines = this->editor->toPlainText().split("\n");
        std::string title = lines.isEmpty() ? "Untitled" : lines[0].toStdString();

        std::thread([this, title, content] {
            DatabaseWorker dbWorker;

            const Note& note = noteManager.add(title, content);

            dbWorker.addNote(note);

            QMetaObject::invokeMethod(this, [this, &note] {
                QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(note.title));
                item->setData(Qt::UserRole, QString::fromStdString(note.id));
                this->noteList->addItem(item);
                this->noteList->setCurrentItem(item);
                this->editor->clear();
            }, Qt::QueuedConnection);

        }).detach();
    });

    // === Splitters ===
    QSplitter* horizontalSplitter = new QSplitter(Qt::Horizontal);
    horizontalSplitter->addWidget(this->catList);
    horizontalSplitter->addWidget(note);
    horizontalSplitter->addWidget(this->noteList);
    horizontalSplitter->addWidget(this->editor);

    horizontalSplitter->setStretchFactor(0, 1);
    horizontalSplitter->setStretchFactor(1, 2);
    horizontalSplitter->setStretchFactor(2, 4);

    this->setCentralWidget(horizontalSplitter);
}

MainWindow::~MainWindow() {}
