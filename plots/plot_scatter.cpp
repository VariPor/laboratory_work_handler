#include "plot_scatter.h"
#include "manager.h"

void PlotScatter::draw(QCustomPlot *plot)
{
    auto m = Manager::instance();

    plot->clearGraphs();
    plot->legend->clear();
    for (int i = 0; i < m->getVarAndCalcCount(); ++i)
    {
        auto* v = m->getVarOrCalc(i);
        if (!v->visual.visible) continue;
        auto graph = plot->addGraph();
        QPen pen;
        pen.setColor(v->visual.color);
        pen.setStyle(v->visual.line_type);
        pen.setWidth(v->visual.width);
        graph->setPen(pen);
        graph->setScatterStyle(v->visual.point_type);
        graph->setName(v->fullNaming);

        QCPErrorBars *errorBars = new QCPErrorBars(plot->xAxis, plot->yAxis);
        errorBars->removeFromLegend();
        errorBars->setDataPlottable(graph);

        QVector<double> x,y,e;

        for (int j = 0; j < v->getMeasurementsCount(); ++j)
        {
            x.append(j);
            y.append(v->measurements[j]);
            e.append(v->instrumentError.value);
        }
        graph->setData(x,y);
        errorBars->setData(e);
    }
    if (plot->plotLayout()->children().size() <= 1)
    {
        plot->plotLayout()->insertRow(0);
        plot->plotLayout()->addElement(0, 0, new QCPTextElement(plot, title));
    }
    static_cast<QCPTextElement* >(plot->plotLayout()->element(0,0))->setText(title);
    plot->xAxis->setLabel(xlable);
    plot->yAxis->setLabel(ylable);
    plot->legend->setVisible(true);
    plot->legend->setBrush(QColor(255, 255, 255, 150));
    plot->rescaleAxes();
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    plot->replot();
}

void PlotScatter::options()
{
    PlotScatterOptionsDialog optionDialog{xlable, ylable, title, this};
    optionDialog.show();
    optionDialog.exec();
    xlable = optionDialog.xlable.text();
    ylable = optionDialog.ylable.text();
    title = optionDialog.title.text();
}

PlotScatterOptionsDialog::PlotScatterOptionsDialog(QString xLable, QString yLable, QString title, QWidget *parent)
    : xlable(xLable), ylable(yLable), title(title),  QDialog{parent}
{
    QVBoxLayout *mainlayout = new QVBoxLayout;

    QLabel *titleLable = new QLabel(tr("Plot title:"));
    mainlayout->addWidget(titleLable);
    mainlayout->addWidget(&this->title);

    QLabel *xLableLable = new QLabel(tr("X axis lable:"));
    mainlayout->addWidget(xLableLable);
    mainlayout->addWidget(&this->xlable);

    QLabel *yLableLable = new QLabel(tr("Y axis lable:"));
    mainlayout->addWidget(yLableLable);
    mainlayout->addWidget(&this->ylable);

    setLayout(mainlayout);
}
