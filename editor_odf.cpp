#include "editor_odf.h"

Q_GLOBAL_STATIC(EditorODF, GlobalEditor)

EditorODF *EditorODF::instance()
{
    return GlobalEditor;
}

void EditorODF::addTextBlock() {
    blocks.push_back(new TextBlock(this->getDocument()));
    cursor.insertText("New text block");
    cursor.insertBlock();
}

void EditorODF::addTableBlock() {
    blocks.push_back(new TableBlock(this->getDocument()));
        // Creating table
    QTextCursor cursor(this->getDocument());
    cursor.insertTable(5, 5);
    for (int r = 0; r < Manager::instance()->getMeasurementsCount(); r++) {
        for (int c = 0; c < Manager::instance()->getVariablesCount(); c++) {
            qInfo() << 1;
            cursor.insertText(QString::number(Manager::instance()->getVariable(c)->measurements.at(r)));
            cursor.movePosition(QTextCursor::NextCell);
        }
    }
}

