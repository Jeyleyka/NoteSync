#include "MainWindow.h"
#include <QMainWindow>
#include <QSplitter>

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

    // === Center (list of notes) ===
    this->noteList = new NotesList(this);

    // === Right (editor) ===
    this->editor = new Editor(this);

    // === Splitters ===
    QSplitter* horizontalSplitter = new QSplitter(Qt::Horizontal);
    horizontalSplitter->addWidget(this->catList);
    horizontalSplitter->addWidget(this->noteList);
    horizontalSplitter->addWidget(this->editor);

    horizontalSplitter->setStretchFactor(0, 1);
    horizontalSplitter->setStretchFactor(1, 2);
    horizontalSplitter->setStretchFactor(2, 4);

    this->setCentralWidget(horizontalSplitter);
}

MainWindow::~MainWindow() {}
