#include "CardEdit.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QIcon>
#include <QPushButton>

CardEdit::CardEdit(const QString& text, const QIcon& icon, QWidget *parent)
    : QWidget{parent}
{
    QWidget* container = new QWidget(this);
    container->setFixedSize(168,32);
    container->setStyleSheet("QWidget {background-color: #303134; border-radius: 5px;} QWidget:hover {background-color: #414246;}");

    QPushButton* btn = new QPushButton(this);
    btn->setIcon(icon);
    btn->setIconSize(QSize(16,16));
    btn->setText(text);
    btn->setStyleSheet("font-size: 15px; color: #BFC1C4; font-weight: 600; background-color: transparent;");

    QHBoxLayout* containerLayout = new QHBoxLayout(container);
    containerLayout->setContentsMargins(0,0,0,0);
    containerLayout->addWidget(btn);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addWidget(container);
}
