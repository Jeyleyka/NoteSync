#include "NoteInterface.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

NoteInterface::NoteInterface(const QString& id, const QColor& color, const QString& title, const QString content, QWidget *parent)
    : QWidget{parent}
{
    setFixedSize(1080, 375);

    QWidget* container = new QWidget(this);

    QWidget* header = new QWidget();
    header->setFixedSize(1080, 116);
    header->setStyleSheet("border-top-left-radius: 5px; border-top-right-radius: 5px; border-bottom-left-radius: 0px;"
                                " border-bottom-right-radius: 0px; background-color:" + color.name());

    QPushButton* changeCover = new QPushButton(this);
    changeCover->setIcon(QIcon(":/Resources/img.svg"));
    changeCover->setIconSize(QSize(20, 20));
    changeCover->setFixedSize(32,32);
    changeCover->setStyleSheet(
        "QPushButton {"
        "   background-color: transparent;"   // по умолчанию прозрачная
        "   border: none;"
        "   border-radius: 16px;"             // половина ширины = круг
        "}"
        "QPushButton:hover {"
        "   background-color: rgba(83,63,4,255);"
        "}"
        );

    QPushButton* dots = new QPushButton(this);
    dots->setIcon(QIcon(":/Resources/dots.svg"));
    dots->setIconSize(QSize(20, 20));
    dots->setFixedSize(32,32);
    dots->setStyleSheet(
        "QPushButton {"
        "   background-color: transparent;"   // по умолчанию прозрачная
        "   border: none;"
        "   border-radius: 16px;"             // половина ширины = круг
        "}"
        "QPushButton:hover {"
        "   background-color: rgba(83,63,4,255);"  // подсветка кругом
        "}"
    );

    QPushButton* close = new QPushButton(this);
    close->setIcon(QIcon(":/Resources/close.svg"));
    close->setIconSize(QSize(20, 20));
    close->setFixedSize(32,32);
    close->setStyleSheet(
        "QPushButton {"
        "   background-color: transparent;"   // по умолчанию прозрачная
        "   border: none;"
        "   border-radius: 16px;"             // половина ширины = круг
        "}"
        "QPushButton:hover {"
        "   background-color: rgba(83,63,4,255);"  // подсветка кругом
        "}"
        );

    connect(close, &QPushButton::clicked, this, [this] {
        this->close();
    });

    QHBoxLayout* headerLayout = new QHBoxLayout(header);
    headerLayout->setAlignment(Qt::AlignTop);
    headerLayout->addStretch();
    headerLayout->addWidget(changeCover);
    headerLayout->addWidget(dots);
    headerLayout->addWidget(close);
    headerLayout->setContentsMargins(0,15,55,0);

    QWidget* info = new QWidget();
    info->setFixedSize(620, 259);
    info->setStyleSheet("border-bottom-left-radius: 5px; background-color: #242528");

    QPushButton *check = new QPushButton(info);
    check->setIcon(QIcon(":/Resources/empty-check.svg"));
    check->setIconSize(QSize(20,20));
    check->setStyleSheet("background-color: transparent; border: none; border-radius: 10px;");
    check->setFixedSize(20, 20);
    // check->setHidden(true);

    connect(check, &QPushButton::clicked, this, [check, this] {
        if (!checked) {
            check->setIcon(QIcon(":/Resources/full-check.svg"));
            check->setIconSize(QSize(23,23));
            checked = true;
        } else {
            check->setIcon(QIcon(":/Resources/empty-check.svg"));
            check->setIconSize(QSize(20,20));
            checked = false;
        }
    });

    QLabel* text_m = new QLabel(title, this);
    text_m->setStyleSheet("font-size: 28px; font-weight: 700; color: #fff");

    QPushButton* add = addBtn(":/Resources/plus.svg", "Add", info);
    QPushButton* label = addBtn(":/Resources/plus.svg", "Label", info);
    QPushButton* date = addBtn(":/Resources/plus.svg", "Dates", info);
    QPushButton* list = addBtn(":/Resources/plus.svg", "Check-list", info);
    QPushButton* participants = addBtn(":/Resources/plus.svg", "Participants", info);

    // QPushButton* btn = new QPushButton(info);
    // btn->setIcon(QIcon(":/Resources/plus.svg"));
    // btn->setFixedSize(101, 32);
    // btn->setIconSize(QSize(20,20));
    // btn->setText("Add");
    // btn->setStyleSheet("background-color: transparent; border-radius: 5px; border: 1px solid #37383D; color: #fff; font-size: 15px; font-weight: 600;");

    QHBoxLayout* titleLayout = new QHBoxLayout();
    titleLayout->setAlignment(Qt::AlignTop);
    titleLayout->addWidget(check);
    titleLayout->addWidget(text_m);
    titleLayout->setContentsMargins(15,0,0,0);

    QHBoxLayout* btnsLayout = new QHBoxLayout();
    btnsLayout->setContentsMargins(15,0,0,0);
    btnsLayout->addWidget(add);
    btnsLayout->addWidget(label);
    btnsLayout->addWidget(date);
    btnsLayout->addWidget(list);
    btnsLayout->addWidget(participants);

    QVBoxLayout* infoLayout = new QVBoxLayout(info);
    infoLayout->setContentsMargins(0,0,0,0);
    infoLayout->setSpacing(0);
    infoLayout->addLayout(titleLayout);
    infoLayout->addLayout(btnsLayout);

    QVBoxLayout* containerLayout = new QVBoxLayout(container);
    containerLayout->setSpacing(0);
    containerLayout->setContentsMargins(0, 0, 0, 0);
    containerLayout->addWidget(header);
    containerLayout->addWidget(info);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(container);
}

QPushButton* NoteInterface::addBtn(const QString& iconPath, const QString& text, QWidget* parent) {
    QPushButton* btn = new QPushButton(parent);
    btn->setIcon(QIcon(iconPath));
    btn->setFixedSize(101, 32);
    btn->setIconSize(QSize(20,20));
    btn->setText(text);
    btn->setStyleSheet("background-color: transparent; border-radius: 5px; border: 1px solid #37383D; color: #fff; font-size: 15px; font-weight: 600;");
    return btn;
}
