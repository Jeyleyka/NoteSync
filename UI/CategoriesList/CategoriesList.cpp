#include "CategoriesList.h"
#include <QListWidget>

CategoriesList::CategoriesList(QWidget *parent)
    : QListWidget{parent}
{
    addItem("📒 Personal");
    addItem("💼 Work");
    addItem("📚 Study");
}
