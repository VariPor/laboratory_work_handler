#include "plot_hist.h"
#include "manager.h"

void PlotHistogram::draw(QCustomPlot *plot)
{
    auto m = Manager::instance();

    plot->clearGraphs();
    for (int i = 0; i < m->getVariablesCount(); ++i)
    {
        auto & v = m->variables[i];
        if (!v.visual.visible) continue;
        auto graph = plot->addGraph();
        QPen pen;
        pen.setColor(v.visual.color);
        pen.setStyle(v.visual.line_type);
        pen.setWidth(v.visual.width);
        graph->setPen(pen);
        graph->setName(v.fullNaming);
        graph->setLineStyle(QCPGraph::LineStyle::lsStepCenter);

        double min = v.measurements[0], max = v.measurements[0];
        for (double k : v.measurements)
        {
            min = std::min(k, min);
            max = std::max(k, max);
        }

        double step = (max - min) / bins;

        QVector<double> x,y;
        x.append(min - step/2);
        y.append(0);

        for (int j = 0; j < bins; ++j)
        {
            double x0 = min + j * step, x1 = min + (j + 1) * step;
            if ( j == bins - 1) x1 += 1e-10;
            int count = 0;

            for (double k : v.measurements)
            {
                if (x0 <= k && k < x1) count ++;
            }

            x.append((x0+x1)/2);
            y.append(count);
        }
        x.append(max + step/2);
        y.append(0);
        graph->setData(x,y);
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

void PlotHistogram::options()
{
    PlotHistogramOptionsDialog optionDialog{xlable, ylable, title, bins, this};
    optionDialog.show();
    optionDialog.exec();
    xlable = optionDialog.xlable.text();
    ylable = optionDialog.ylable.text();
    title = optionDialog.title.text();
    bins = optionDialog.bins.value();
}

PlotHistogramOptionsDialog::PlotHistogramOptionsDialog(QString xLable, QString yLable, QString title, int bins, QWidget *parent)
    : xlable(xLable), ylable(yLable), title(title), QDialog{parent}
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

    QLabel *binsLable = new QLabel(tr("Bin count:"));
    mainlayout->addWidget(binsLable);
    this->bins.setValue(bins);
    mainlayout->addWidget(&this->bins);

    setLayout(mainlayout);
}
