#ifndef EDITOR_ODF_H
#define EDITOR_ODF_H

#include <QList>
#include <QGlobalStatic>
#include "block.h"


class EditorODF
{

    //QTextDocument* document;
    //QTextCursor cursor;

public:
    void removeBlock();
    void addPlotBlock(QCustomPlot* plot);
    void addTextBlock();
    void addTableBlock();
    void exportBlocks();
    void moveBlockUp();
    void moveBlockDown();
    TextBlock* textBlock() { return blocks.back()->textBlock(); }
    TableBlock* tableBlock() { return blocks.back()->tableBlock(); }
    PlotBlock* plotBlock() { return blocks.back()->plotBlock(); }

    //QTextDocument* getDocument() { return document; }
    //QTextCursor* getCursor() { return &cursor; }

    static EditorODF* instance();
    QList<Block*> blocks;


    EditorODF() { }

};

#endif // EDITOR_ODF_H
