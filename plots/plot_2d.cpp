#include "plot_2d.h"
#include "manager.h"

Plot2d::Plot2d(QString xLable, QString yLable, QWidget *parent) : Plot(parent), xLable{xLable}, yLable{yLable} {}

void Plot2d::draw(QCustomPlot *plot)
{
    auto m = Manager::instance();
    VariableData *xv = m->getVariable(xLable), *yv = m->getVariable(yLable);

    plot->clearGraphs();
    plot->legend->setVisible(false);
    if (!yv)
    {
        if (m->getVariableCount() > 0)
        {
            xv = m->getVariable(0);
            yv = m->getVariable(0);
        } else return;
    }

    auto graph = plot->addGraph();
    QPen pen;
    graph->setPen(pen);
    graph->setScatterStyle(yv->visual.point_type);
    graph->setLineStyle(QCPGraph::lsNone);

    QCPErrorBars *errorBarsX = new QCPErrorBars(plot->xAxis, plot->yAxis);
    QCPErrorBars *errorBarsY = new QCPErrorBars(plot->yAxis, plot->xAxis);
    errorBarsX->setDataPlottable(graph);
    errorBarsY->setDataPlottable(graph);

    QVector<double> x,y,ex,ey;
    for (int j = 0; j < xv->getMeasurementCount(); ++j)
    {
        x.append(xv->measurements[j]);
        y.append(yv->measurements[j]);
        ex.append(xv->instrumentError.value);
        ey.append(yv->instrumentError.value);
    }
    graph->setData(x,y);
    errorBarsX->setData(ex);
    errorBarsY->setData(ey);
    if (plot->plotLayout()->children().size() <= 1)
    {
        plot->plotLayout()->insertRow(0);
        plot->plotLayout()->addElement(0, 0, new QCPTextElement(plot, title));
    }
    static_cast<QCPTextElement* >(plot->plotLayout()->element(0,0))->setText(title);
    plot->xAxis->setLabel(xv->fullNaming);
    plot->yAxis->setLabel(yv->fullNaming);
    plot->rescaleAxes();
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    plot->replot();
}

void Plot2d::options()
{
    Plot2dOptionsDialog optionDialog{xLable, yLable, title, this};
    optionDialog.show();
    optionDialog.exec();
    xLable = Manager::instance()->getVariable(optionDialog.xLable.currentText())->shortNaming;
    yLable = Manager::instance()->getVariable(optionDialog.yLable.currentText())->shortNaming;
    title = optionDialog.title.text();
}

Plot2dOptionsDialog::Plot2dOptionsDialog(QString xlable, QString ylable, QString title, QWidget *parent)
    : title(title),  QDialog{parent}
{
    QVBoxLayout *mainlayout = new QVBoxLayout;

    QLabel *titleLable = new QLabel(tr("Plot title:"));
    mainlayout->addWidget(titleLable);
    mainlayout->addWidget(&this->title);

    QLabel *xLableLable = new QLabel(tr("X axis lable:"));
    mainlayout->addWidget(xLableLable);
    this->xLable.clear();

    auto* m = Manager::instance();
    for (int i = 0; i < m->getVariableCount(); ++i)
    {
        this->xLable.addItem(m->getVariable(i)->fullNaming);
        if (m->getVariable(i)->shortNaming == xlable)
            this->xLable.setCurrentIndex(this->xLable.count() - 1);
    }
    mainlayout->addWidget(&this->xLable);

    QLabel *yLableLable = new QLabel(tr("Y axis lable:"));
    mainlayout->addWidget(yLableLable);
    this->yLable.clear();
    for (int i = 0; i < Manager::instance()->getVariableCount(); ++i)
    {
        this->yLable.addItem(Manager::instance()->getVariable(i)->fullNaming);
        if (Manager::instance()->getVariable(i)->shortNaming == ylable)
            this->yLable.setCurrentIndex(this->yLable.count() - 1);
    }
    mainlayout->addWidget(&this->yLable);

    setLayout(mainlayout);
}


