#ifndef PLOT_HIST_H
#define PLOT_HIST_H


#include "plot.h"

class PlotHistogramOptionsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PlotHistogramOptionsDialog(QString xLable, QString yLable, QString title, int bins, QWidget *parent = nullptr);
    QLineEdit xlable, ylable, title;
    QSpinBox bins;
};

class PlotHistogram : public Plot
{
    Q_OBJECT
public:
   PlotHistogram(QWidget *parent = nullptr) : Plot(parent) {};
   ~PlotHistogram() {};

    void draw(QCustomPlot *plot) override;
    void options() override;
    QString xlable = "Measurement value", ylable = "Measurement count", title = "";
    int bins = 10;
};

#endif // PLOT_HIST_H
