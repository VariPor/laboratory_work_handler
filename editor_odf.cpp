#include "editor_odf.h"
#include "qcpdocumentobject.h"

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
    cursor.insertTable(5, 5);
    qInfo() << 8;
    for (int r = 0; r < Manager::instance()->getMeasurementsCount(); r++) {
        for (int c = 0; c < Manager::instance()->getVariablesCount(); c++) {
            qInfo() << 1;
            cursor.insertText(QString::number(Manager::instance()->getVariable(c)->measurements.at(r)));
            cursor.movePosition(QTextCursor::NextCell);
        }
    }
}

void EditorODF::addPlotBlock(QCustomPlot* plot) {
    blocks.push_back(new PlotBlock(this->getDocument()));

    // register the plot document object (only needed once, no matter how many plots will be in the QTextDocument):
    QCPDocumentObject *plotObjectHandler = new QCPDocumentObject(EditorODF::instance()->getDocument());
    EditorODF::instance()->getDocument()->documentLayout()->registerHandler(QCPDocumentObject::PlotTextFormat, plotObjectHandler);


    // insert the current plot at the cursor position. QCPDocumentObject::generatePlotFormat creates a
    // vectorized snapshot of the passed plot (with the specified width and height) which gets inserted
    // into the text document.
    double width = plot->width();
    double heigh = plot->height();
    EditorODF::instance()->getCursor()->insertText(QString(QChar::ObjectReplacementCharacter),
                      QCPDocumentObject::generatePlotFormat(plot, width, heigh));
}
