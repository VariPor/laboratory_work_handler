#ifndef PLOT_2D_H
#define PLOT_2D_H

#include "plot.h"

class Plot2dOptionsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit Plot2dOptionsDialog(QString xlable, QString ylable, QString title, QWidget *parent = nullptr);
    QLineEdit title;
    QComboBox xLable, yLable;
};

class Plot2d : public Plot
{
    Q_OBJECT
public:
   Plot2d(QString xlable, QString ylable, QWidget *parent = nullptr);;
   ~Plot2d() {};

    void draw(QCustomPlot *plot) override;
    void options() override;
    QString xLable, yLable, title = "";
};

#endif // PLOT_2D_H
