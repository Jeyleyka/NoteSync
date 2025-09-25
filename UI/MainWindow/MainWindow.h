#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "../Header/Header.h"
#include "../CategoriesList/CategoriesList.h"
#include "../../Persistance/Database/Database.h"
#include "../NotesList/NotesList.h"
#include "../Editor/Editor.h"
#include "../../Core/Note/Note.h"
#include "../../Core/NoteManager/NoteManager.h"

class NoteUI;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    NoteManager noteManager;
    Header* header;
    CategoriesList* catList;
    NotesList* noteList;
    Editor* editor;
};
#endif // MAINWINDOW_H
