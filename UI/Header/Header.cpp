#include "Header.h"

#include <QToolBar>
#include <QLineEdit>
#include <QAction>

Header::Header(QWidget *parent)
    : QWidget{parent}
{
    toolBar = new QToolBar("Main Toolbar", this);
    QAction* addAction = toolBar->addAction("➕ Add");
    QAction* deleteAction = toolBar->addAction("🗑 Delete");
    QAction* saveAction = toolBar->addAction("💾 Save");

    connect(addAction, &QAction::triggered, this, &Header::onAddNote);

    toolBar->addSeparator();
    QLineEdit* searchBox = new QLineEdit();
    searchBox->setPlaceholderText("Search notes...");
    toolBar->addWidget(searchBox);
}
