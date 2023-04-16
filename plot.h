#ifndef PLOT_H
#define PLOT_H

#include <QWidget>
#include "qcustomplot.h"
#include "variable_data.h"

class Plot : public  QWidget
{
    Q_OBJECT
public:
    Plot(QWidget *parent = nullptr) : QWidget(parent) {};
    ~Plot() = default;

    virtual void draw(QCustomPlot *plot) = 0;
    virtual void options() = 0;
};

#endif // PLOT_H
