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

    connect(this->header, &Header::onAddNote, this, [this] {
        Database& db = Database::instance();

        std::string content = this->editor->toPlainText().toStdString();

        QStringList lines = this->editor->toPlainText().split("\n");
        std::string title = lines.isEmpty() ? "Untitled" : lines[0].toStdString();

        const Note& note = noteManager.add(title, content);

        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(note.title));
        item->setData(Qt::UserRole, QString::fromStdString(note.id));

        db.insertNoteToDB(QString::fromStdString(note.id), QString::fromStdString(note.title), QString::fromStdString(note.content));

        this->noteList->addItem(item);
        this->noteList->setCurrentItem(item);
        this->editor->clear();
    });

    // === Sidebar (categories) ===
    this->catList = new CategoriesList(this);

    // === Center (list of notes) ===
    this->noteList = new NotesList(this);

    connect(this->noteList, &NotesList::itemDoubleClicked, this, [this](QListWidgetItem* item) {
        this->editor->setText(item->text());
    });

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
