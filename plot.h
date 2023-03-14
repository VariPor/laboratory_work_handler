#ifndef PLOT_H
#define PLOT_H

#include <QTabWidget>

class Plot
{
public:
    virtual void draw() = 0;
    virtual void options() = 0;
};

class ChoicePlot : Plot
{
    QTabWiddget<Plot> plots;
};

class ScatterPlot : Plot
{
    QString title;
    std::pair<QString, QString> axisNames;
public:
    void draw() override;
    void options() override;
};

class HistogramPlot : Plot
{
    QString title;
    std::pair<QString, QString> axisNames;
    double binCount;
public:
    void draw() override;
    void options() override;
};

class ScatterPlot2D : Plot
{
    QString title;
    std::pair<QString, QString> axisNames;
    QString xVariable;
    QString yVariable;
public:
    void draw() override;
    void options() override;
};

class ColormapPlot2D : Plot
{
    QString title;
    std::pair<QString, QString> axisNames;
    QString xVariable;
    QString yVariable;
    double binCount;
public:
    void draw() override;
    void options() override;
};


#endif // PLOT_H
