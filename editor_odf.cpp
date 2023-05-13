#include "editor_odf.h"
#include "qcustomplot.h"

Q_GLOBAL_STATIC(EditorODF, GlobalEditor)

EditorODF *EditorODF::instance()
{
    return GlobalEditor;
}

void EditorODF::addTextBlock(QVBoxLayout* blockHolder, int number) {
    blocks.push_back(new TextBlock(blockHolder, number));
}

void EditorODF::addTableBlock(QVBoxLayout* blockHolder, int number) {
    blocks.push_back(new TableBlock(blockHolder, number));
}

void EditorODF::addPlotBlock(QCustomPlot* plot, QVBoxLayout* blockHolder, int number) {

    QPixmap pixmap = plot->toPixmap(400, 400);

    blocks.push_back(new PlotBlock(pixmap, blockHolder, number));
}
