#ifndef CARDEDIT_H
#define CARDEDIT_H

#include <QWidget>

class CardEdit : public QWidget
{
    Q_OBJECT
public:
    explicit CardEdit(const QString& text, const QIcon& icon, QWidget *parent = nullptr);

signals:
};

#endif // CARDEDIT_H
