#ifndef EDITOR_ODF_H
#define EDITOR_ODF_H

#include <QList>
#include <QGlobalStatic>
#include "block.h"


class EditorODF
{
public:
    void removeBlock();
    void addPlotBlock(QCustomPlot* plot);
    void addTextBlock();
    void addTableBlock();
    void moveBlockUp();
    void moveBlockDown();
    TextBlock* textBlock() { return blocks.back()->textBlock(); }
    TableBlock* tableBlock() { return blocks.back()->tableBlock(); }
    PlotBlock* plotBlock() { return blocks.back()->plotBlock(); }

    static EditorODF* instance();
    QList<Block*> blocks;


    EditorODF() { }

};

#endif // EDITOR_ODF_H
