#ifndef PLOT_CHOISE_H
#define PLOT_CHOISE_H

#include "plot.h"

class PlotChoiseOptionsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PlotChoiseOptionsDialog(QString currentPlot, QStringList plots, QWidget *parent = nullptr);
    QComboBox currentPlot;
private slots:
    void options();
};

class PlotChoise : public Plot
{
    Q_OBJECT
public:
   PlotChoise (QMap<QString, Plot*> plots, QWidget *parent = nullptr) :  Plot(parent), plots{plots}, currentPlot{plots.keys()[2]} { }
   ~PlotChoise() {};

    void draw(QCustomPlot *plot) override;
    void options() override;
    QMap<QString, Plot*> plots;
    QString currentPlot;
    void optionsCurrentPlot(QString currentPlot);
};

#endif // PLOT_CHOISE_H
