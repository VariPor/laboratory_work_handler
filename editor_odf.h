#ifndef EDITOR_ODF_H
#define EDITOR_ODF_H

#include <QList>
#include "block.h"

class EditorODF
{
    QList<Block> blocks;
public:
    void removeBlock(Block);
    void addPlotBlock();
    void addTextBlock();
    void addTableBlock();
    void exportBlocks();
    void moveBlockUp();
    void moveBlockDown();
};

#endif // EDITOR_ODF_H
