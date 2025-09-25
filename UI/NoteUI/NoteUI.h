#ifndef NOTEUI_H
#define NOTEUI_H

#include <QWidget>
#include <QEvent>
#include <QObject>
#include <QPushButton>

class NoteUI : public QWidget
{
    Q_OBJECT

public:
    explicit NoteUI(const QColor& color, const QString& text, QWidget* parent = nullptr);

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    QWidget* container;
    QPushButton* changeNote;
};

#endif // NOTEUI_H
