#ifndef EDITOR_ODF_H
#define EDITOR_ODF_H

#include <QList>
#include <QGlobalStatic>
#include "block.h"


class EditorODF
{
public:
    void addPlotBlock(QCustomPlot* plot, QVBoxLayout* blockHolder, int number);
    void addTextBlock(QVBoxLayout* blockHolder, int number);
    void addTableBlock(QVBoxLayout* blockHolder, int number);

    static EditorODF* instance();
    QList<Block*> blocks;

    EditorODF() { }

};

#endif // EDITOR_ODF_H
