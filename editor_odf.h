#ifndef EDITOR_ODF_H
#define EDITOR_ODF_H

#include <QList>
#include <QGlobalStatic>
#include "block.h"


class EditorODF
{
    QList<Block*> blocks;
    QTextDocument* document;
    QTextCursor cursor;

public:
    void removeBlock();
    void addPlotBlock(QCustomPlot* plot);
    void addTextBlock();
    void addTableBlock();
    void exportBlocks();
    void moveBlockUp();
    void moveBlockDown();
    void createDocument(QObject* parent);

    QTextDocument* getDocument() { return document; }
    QTextCursor* getCursor() { return &cursor; }

    static EditorODF* instance();

    EditorODF() {  }

};

#endif // EDITOR_ODF_H
