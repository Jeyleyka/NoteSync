#ifndef CATEGORIESLIST_H
#define CATEGORIESLIST_H

#include <QWidget>
#include <QListWidget>

class CategoriesList : public QListWidget
{
    Q_OBJECT
public:
    explicit CategoriesList(QWidget *parent = nullptr);
};

#endif // CATEGORIESLIST_H
