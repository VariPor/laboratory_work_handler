#ifndef PLOT_SCATTER_H
#define PLOT_SCATTER_H

#include "plot.h"

class PlotScatterOptionsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PlotScatterOptionsDialog(QString xLable, QString yLable, QString title, QWidget *parent = nullptr);
    QLineEdit xlable, ylable, title;
};

class PlotScatter : public Plot
{
    Q_OBJECT
public:
   PlotScatter(QWidget *parent = nullptr) : Plot(parent) {};
   ~PlotScatter() {};

    void draw(QCustomPlot *plot) override;
    void options() override;
    QString xlable = "Measurement count", ylable = "Measurement value", title = "";
};
#endif // PLOT_SCATTER_H
