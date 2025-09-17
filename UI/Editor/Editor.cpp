#include "Editor.h"

Editor::Editor(QWidget *parent)
    : QTextEdit{parent}
{
    setPlaceholderText("Write your note here...");
    setStyleSheet("QTextEdit { font-size: 16px; padding: 10px; }");
}
