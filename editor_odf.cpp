#include "editor_odf.h"
#include "qcpdocumentobject.h"
#include "qcustomplot.h"

Q_GLOBAL_STATIC(EditorODF, GlobalEditor)

EditorODF *EditorODF::instance()
{
    return GlobalEditor;
}

void EditorODF::addTextBlock() {
    blocks.push_back(new TextBlock());
}

void EditorODF::addTableBlock() {
    blocks.push_back(new TableBlock());
    auto* table = blocks.back()->tableBlock()->table;

    // Creating table
    auto* manager = Manager::instance();
    table->setColumnCount(manager->getVariablesCount());
    table->setRowCount(manager->getMeasurementsCount());

    for (int i = 0; i < manager->getVariablesCount(); ++i) {
        QTableWidgetItem* item = new QTableWidgetItem (manager->getVariable(i)->shortNaming);
        table->setHorizontalHeaderItem(i, item);
    }

    for (int i = 0; i < manager->getVariablesCount(); ++i)
        for (int j = 0; j < manager->getMeasurementsCount(); ++j) {
                QTableWidgetItem* item = new QTableWidgetItem
                        (QString::number(manager->getVariable(i)->measurements.at(j)), QTableWidgetItem::Type);
                table->setItem(j, i, item);
                table->item(j, i)->setFlags(Qt::NoItemFlags);
        }
}

void EditorODF::addPlotBlock(QCustomPlot* plot) {


    QPixmap pixmap = plot->toPixmap(300, 300);

    blocks.push_back(new PlotBlock(pixmap));
    blocks.back()->plotBlock()->label->setPixmap(pixmap);
}
