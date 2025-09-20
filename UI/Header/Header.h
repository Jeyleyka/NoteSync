#ifndef HEADER_H
#define HEADER_H

#include <QWidget>
#include <QToolBar>

class Header : public QWidget
{
    Q_OBJECT
public:
    explicit Header(QWidget *parent = nullptr);
    QToolBar* getToolBar() const { return toolBar; }

signals:
    void onAddNote();
    void onRemoveNote();

private:
    QToolBar* toolBar;
};

#endif // HEADER_H
