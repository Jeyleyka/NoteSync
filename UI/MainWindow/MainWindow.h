#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "../Header/Header.h"
#include "../CategoriesList/CategoriesList.h"
#include "../../Persistance/Database/Database.h"
#include "../NotesList/NotesList.h"
#include "../Editor/Editor.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Header* header;
    CategoriesList* catList;
    NotesList* noteList;
    Editor* editor;
};
#endif // MAINWINDOW_H
