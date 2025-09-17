#ifndef EDITOR_H
#define EDITOR_H

#include <QWidget>
#include<QTextEdit>

class Editor : public QTextEdit
{
    Q_OBJECT
public:
    explicit Editor(QWidget *parent = nullptr);
};

#endif // EDITOR_H
