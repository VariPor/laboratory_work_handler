#ifndef EDITOR_ODF_H
#define EDITOR_ODF_H

#include <QList>
#include <QGlobalStatic>
#include "block.h"


class EditorODF
{
    QList<Block*> blocks;
    QTextDocument document;
    QTextCursor cursor;

public:
    void removeBlock();
    void addPlotBlock();
    void addTextBlock();
    void addTableBlock();
    void exportBlocks();
    void moveBlockUp();
    void moveBlockDown();

    QTextDocument* getDocument() { return &document; }
    QTextCursor* getCursor() { return &cursor; }

    static EditorODF* instance();

    EditorODF() { cursor = QTextCursor(&document); }

};

#endif // EDITOR_ODF_H
