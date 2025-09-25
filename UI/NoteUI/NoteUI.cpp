#include "NoteUI.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QIcon>
#include <QPushButton>
#include <QLabel>

NoteUI::NoteUI(const QColor& color, const QString& text, QWidget* parent)
    : QWidget(parent)
{
    container = new QWidget(this);
    container->installEventFilter(this);
    container->setFixedSize(256, 84);
    container->setStyleSheet("background-color: #242528; border-radius: 5px;");

    QVBoxLayout* containerLayout = new QVBoxLayout(container);
    containerLayout->setContentsMargins(0,0,0,0);

    changeNote = new QPushButton(this);
    changeNote->setIcon(QIcon(":/Resources/edit.svg"));
    changeNote->setFixedSize(26, 26);
    changeNote->setStyleSheet("background-color: #242528; border-radius: 13px;");
    changeNote->setHidden(true);

    QWidget* buttonWidget = new QWidget();
    buttonWidget->setFixedSize(256, 36);
    buttonWidget->setStyleSheet("background-color:" + color.name());
    QHBoxLayout* buttonLayout = new QHBoxLayout(buttonWidget);
    buttonLayout->addStretch();
    buttonLayout->addWidget(changeNote);

    QLabel* text_m = new QLabel(text, this);

    QVBoxLayout* textLayout = new QVBoxLayout();
    textLayout->addWidget(text_m);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    containerLayout->addWidget(buttonWidget);
    containerLayout->addLayout(textLayout);

    mainLayout->addWidget(container);
}

bool NoteUI::eventFilter(QObject *watched, QEvent *event) {
    if (watched == container) {
        if (event->type() == QEvent::Enter) {
            container->setStyleSheet("background-color: #242528; border-radius: 5px; border: 1px solid #fff");
            changeNote->setHidden(false);
        }
        else if (event->type() == QEvent::Leave) {
            container->setStyleSheet("background-color: #242528; border-radius: 5px;");
            changeNote->setHidden(true);
        }
    }

    return QWidget::eventFilter(watched, event);
}
