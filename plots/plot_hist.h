#ifndef PLOT_HIST_H
#define PLOT_HIST_H

#include "plot.h"

class PlotHistogramOptionsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PlotHistogramOptionsDialog(QString xlable, QString ylable, QString title, int bins, QWidget *parent = nullptr);
    QLineEdit xLable, yLable, title;
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
    QString xLable = "Measurement value", yLable = "Measurement count", title = "";
    int bins = 10;
};

#endif // PLOT_HIST_H
