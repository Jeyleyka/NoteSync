#ifndef NOTEUI_H
#define NOTEUI_H

#include <QWidget>
#include <QEvent>
#include <QObject>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <QVector>
#include <QString>
#include <QColor>

class QKeyEvent;
class CardEdit;

class NoteUI : public QWidget
{
    Q_OBJECT

public:
    explicit NoteUI(const QString& id, const QColor& color, const QString& text, QWidget* parent = nullptr);
    void initCards();

    QString& getId();
    // QColor& getColor();
    QString& getText();

    void setEditEnabled(bool enabled);
    void startEditing();

signals:
    void saveChanges(NoteUI& note);
    void editingStarted(NoteUI* note);
    void editingFinished(NoteUI* note);
    void showInterface(const QString& id, const QColor& color, const QString& title);

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    void finishEditing();

    QWidget* container;

    QPushButton* check;
    QPushButton* changeNote;
    QPushButton* saveEditing;

    QVector<CardEdit*> cards;

    QLabel* text_m;

    QColor color;

    QTextEdit* textEdit;
    QString id;

    QString noteText;

    bool checked = false;
    bool changing = false;
};

#endif // NOTEUI_H
