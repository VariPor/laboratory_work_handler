#include "editor_odf.h"
#include "qcpdocumentobject.h"
#include "qcustomplot.h"

Q_GLOBAL_STATIC(EditorODF, GlobalEditor)

EditorODF *EditorODF::instance()
{
    return GlobalEditor;
}

void EditorODF::addTextBlock() {
    cursor.movePosition(QTextCursor::End);
    blocks.push_back(new TextBlock("New text block"));
    cursor.insertText("New text block");
}

void EditorODF::addTableBlock() {
    cursor.movePosition(QTextCursor::End);
    blocks.push_back(new TableBlock());

    // Creating table
    int var_count = Manager::instance()->getVariablesCount();
    int meas_count = Manager::instance()->getMeasurementsCount();;
    cursor.insertTable(var_count, meas_count + 1);

    for (int r = -1; r < meas_count; r++) {
        for (int c = 0; c < var_count; c++) {
            if (r == -1)
                cursor.insertText(Manager::instance()->getVariable(c)->shortNaming);
            else
                cursor.insertText(QString::number(Manager::instance()->getVariable(c)->measurements.at(r)));
            cursor.movePosition(QTextCursor::NextCell);
        }
    }
}

void EditorODF::addPlotBlock(QCustomPlot* plot) {
    cursor.movePosition(QTextCursor::End);
    double width = plot->width();
    double height = plot->height();
    QPicture picture;
    QCPPainter qcpPainter;
    qcpPainter.begin(&picture);
    plot->toPainter(&qcpPainter, width, height);
    qcpPainter.end();

    blocks.push_back(new PlotBlock(picture));

    // register the plot document object (only needed once, no matter how many plots will be in the QTextDocument):
    QCPDocumentObject *plotObjectHandler = new QCPDocumentObject(EditorODF::instance()->getDocument());
    EditorODF::instance()->getDocument()->documentLayout()->registerHandler(QCPDocumentObject::PlotTextFormat, plotObjectHandler);


    // insert the current plot at the cursor position. QCPDocumentObject::generatePlotFormat creates a
    // vectorized snapshot of the passed plot (with the specified width and height) which gets inserted
    // into the text document.
    EditorODF::instance()->getCursor()->insertText(QString(QChar::ObjectReplacementCharacter),
                      QCPDocumentObject::generatePlotFormat(plot, width, height));

}

void EditorODF::createDocument(QObject* parent) {
    document = new QTextDocument(parent);
    cursor = QTextCursor(document);
    cursor.insertBlock();
}
