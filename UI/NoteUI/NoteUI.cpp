#include "NoteUI.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QIcon>
#include <QKeyEvent>
#include <QResizeEvent>

#include "../CardEdit/CardEdit.h"

NoteUI::NoteUI(const QString& id, const QColor& color, const QString& text, QWidget* parent)
    : QWidget(parent), id(id), color(color), noteText(text)
{
    qApp->installEventFilter(this);
    container = new QWidget(this);
    container->installEventFilter(this);
    container->setFixedSize(256, 84);
    container->setObjectName("mainContainer");
    container->setStyleSheet("background-color: #242528; border-radius: 5px;");

    QVBoxLayout* containerLayout = new QVBoxLayout(container);
    containerLayout->setContentsMargins(0,0,0,0);

    initCards();

    changeNote = new QPushButton(this);
    changeNote->setIcon(QIcon(":/Resources/edit.svg"));
    changeNote->setFixedSize(26, 26);
    changeNote->setObjectName("changeBtn");
    changeNote->setStyleSheet("#changeBtn {background-color: #242528; border-radius: 13px;} #changeBtn:hover {background-color: #34363A}");
    changeNote->setHidden(true);

    QWidget* buttonWidget = new QWidget();
    buttonWidget->setObjectName("btnContainer");
    buttonWidget->setFixedSize(256, 36);
    buttonWidget->setStyleSheet("border-top-left-radius: 5px; border-top-right-radius: 5px; border-bottom-left-radius: 0px;"
    " border-bottom-right-radius: 0px; background-color:" + color.name());
    QHBoxLayout* buttonLayout = new QHBoxLayout(buttonWidget);
    buttonLayout->addStretch();
    buttonLayout->addWidget(changeNote);

    check = new QPushButton(this);
    check->setIcon(QIcon(":/Resources/empty-check.svg"));
    check->setIconSize(QSize(20,20));
    check->setStyleSheet("background-color: transparent; border: none; border-radius: 10px;");
    check->setFixedSize(20, 20);
    check->setHidden(true);

    connect(check, &QPushButton::clicked, this, [this] {
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

    text_m = new QLabel(noteText, this);
    text_m->setStyleSheet("font-size: 15px; color: #fff");

    textEdit = new QTextEdit(this);
    textEdit->installEventFilter(this);
    textEdit->setStyleSheet("font-size: 15px; border: none; background-color: transparent;");
    textEdit->setHidden(true);

    QHBoxLayout* textLayout = new QHBoxLayout();
    textLayout->addWidget(check);
    textLayout->addWidget(text_m);
    textLayout->addWidget(textEdit);
    textLayout->setContentsMargins(15,0,0,0);

    saveEditing = new QPushButton("Save");
    saveEditing->setObjectName("saveBtn");
    saveEditing->setFixedSize(93,32);
    saveEditing->setStyleSheet("#saveBtn {background-color: #669DF1; color: #1F1F21; font-size: 15px; font-weight: 600;}"
                               "#saveBtn:hover {background-color: #6CA7FF;}");
    saveEditing->setHidden(true);

    connect(saveEditing, &QPushButton::clicked, this, [this] {
        QString newText = textEdit->toPlainText().trimmed(); // trim чтобы не оставить "   "

        if (newText.isEmpty())
            return;

        noteText = newText;
        finishEditing();

        emit saveChanges(*this);
    });

    containerLayout->addWidget(buttonWidget);
    containerLayout->addLayout(textLayout);

    for (auto& c : cards)
        c->setHidden(true);

    connect(changeNote, &QPushButton::clicked, this, [this] {
        emit editingStarted(this);

        changing = true;

        for (auto& c : cards)
            c->setHidden(false);

        textEdit->setText(noteText);
        textEdit->selectAll();
        text_m->setHidden(true);
        check->setHidden(true);
        textEdit->setHidden(false);
        textEdit->setFocus();
        saveEditing->setHidden(false);
        container->setFixedSize(256, 130);
    });

    QVBoxLayout* noteLayout = new QVBoxLayout();
    noteLayout->setContentsMargins(0,50,0,0);
    noteLayout->setSpacing(0);
    noteLayout->addStretch(0);
    noteLayout->addWidget(container);
    noteLayout->addWidget(saveEditing);
    noteLayout->addStretch(0);

    QVBoxLayout* cardsLayout = new QVBoxLayout();
    cardsLayout->setContentsMargins(0,0,0,60);
    cardsLayout->setSpacing(5);
    cardsLayout->addStretch(0);

    for (auto& c : cards)
        cardsLayout->addWidget(c);

    cardsLayout->addStretch();

    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->addLayout(noteLayout);
    mainLayout->addLayout(cardsLayout);
}

void NoteUI::initCards() {
    CardEdit* openCard = new CardEdit("Open card", QIcon(":/Resources/openCard.svg"), this);
    CardEdit* changeCover = new CardEdit("Change cover", QIcon(":/Resources/changeCover.svg"), this);

    cards.push_back(openCard);
    cards.push_back(changeCover);
}

QString& NoteUI::getId() {
    return this->id;
}

// QColor& NoteUI::getColor() {
//     // return QColor("");
// }

QString& NoteUI::getText() {
    return noteText;
}

void NoteUI::setEditEnabled(bool enabled) {
    changeNote->setEnabled(enabled);
}

bool NoteUI::eventFilter(QObject *watched, QEvent *event) {
    if (watched == container) {
        if (event->type() == QEvent::Enter) {
            container->setStyleSheet("#mainContainer {"
                                     " background-color: #242528;"
                                     " border-radius: 5px;"
                                     "}"
                                     "#btnContainer {"
                                     " border-radius: 5px;"
                                     "}");

            changeNote->setHidden(false);

            if (!changing)
                check->setHidden(false);
        }
        else if (event->type() == QEvent::Leave) {
            container->setStyleSheet("#mainContainer {"
                                     " background-color: #242528;"
                                     " border-radius: 5px;"
                                     "}"
                                     "#btnContainer {"
                                     " border-radius: 5px;"
                                     "}");
            changeNote->setHidden(true);

            if (!checked || changing)
                check->setHidden(true);
        }
    } else if (watched == textEdit && event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);

        if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) {
            if (changing) {
                QString newText = textEdit->toPlainText().trimmed();

                if (newText.isEmpty())
                    return true;

                noteText = textEdit->toPlainText();
                finishEditing();
                emit saveChanges(*this);

                return true;
            }
        }
    } else if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);

        // если кликнули не внутри NoteUI
        if (!this->rect().contains(this->mapFromGlobal(mouseEvent->globalPosition().toPoint()))) {
            finishEditing();
        }
    } else if (watched == container && event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);

        if (this->rect().contains(this->mapFromGlobal(mouseEvent->globalPosition().toPoint())))
            emit showInterface(id, color, noteText);
    }

    return QWidget::eventFilter(watched, event);
}

void NoteUI::mousePressEvent(QMouseEvent *event) {
    if (container->rect().contains(container->mapFromParent(event->pos()))) {
        emit showInterface(id, color, noteText);
    }
    QWidget::mousePressEvent(event);
}

void NoteUI::startEditing() {
    changing = true;
    textEdit->setHidden(false);
    text_m->setHidden(true);
    saveEditing->setHidden(false);
}

void NoteUI::finishEditing() {
    changing = false;

    for (auto& c : cards)
        c->setHidden(true);

    container->setFixedSize(256, 84);
    text_m->setText(noteText);
    text_m->setHidden(false);
    textEdit->setHidden(true);
    saveEditing->setHidden(true);
    emit editingFinished(this);
}
