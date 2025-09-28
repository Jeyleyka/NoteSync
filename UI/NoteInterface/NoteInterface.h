#ifndef NOTEINTERFACE_H
#define NOTEINTERFACE_H

#include <QWidget>

class QPushButton;

class NoteInterface : public QWidget
{
    Q_OBJECT
public:
    explicit NoteInterface(const QString& id, const QColor& color, const QString& title, const QString content, QWidget *parent = nullptr);

signals:

private:
    QPushButton* addBtn(const QString& iconPath, const QString& text, QWidget* parent);

    bool checked = false;
};

#endif // NOTEINTERFACE_H
