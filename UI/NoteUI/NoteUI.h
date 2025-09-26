#ifndef NOTEUI_H
#define NOTEUI_H

#include <QWidget>
#include <QEvent>
#include <QObject>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <QVector>

class QKeyEvent;
class CardEdit;

class NoteUI : public QWidget
{
    Q_OBJECT

public:
    explicit NoteUI(const QColor& color, const QString& text, QWidget* parent = nullptr);
    void initCards();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    QWidget* container;

    QPushButton* check;
    QPushButton* changeNote;
    QPushButton* saveEditing;

    QVector<CardEdit*> cards;

    QLabel* text_m;

    QTextEdit* textEdit;

    bool checked = false;
    bool changing = false;
};

#endif // NOTEUI_H
