#include "plot_choise.h"
#include "manager.h"

void PlotChoise::draw(QCustomPlot *plot)
{
    plots[currentPlot]->draw(plot);
}

void PlotChoise::options()
{
    PlotChoiseOptionsDialog optionDialog{currentPlot, plots.keys(), this};
    optionDialog.show();
    optionDialog.exec();
    currentPlot = optionDialog.currentPlot.currentText();
}

void PlotChoise::optionsCurrentPlot(QString currentPlot)
{
    plots[currentPlot]->options();
}

PlotChoiseOptionsDialog::PlotChoiseOptionsDialog(QString currentPlot, QStringList plots, QWidget *parent)
    :  QDialog{parent}
{
    QVBoxLayout *mainlayout = new QVBoxLayout;

    QLabel *chooseLable = new QLabel(tr("Chosen plot:"));
    mainlayout->addWidget(chooseLable);
    this->currentPlot.insertItems(0, plots);
    this->currentPlot.setCurrentText(currentPlot);
    mainlayout->addWidget(&this->currentPlot);

    QLabel *optionsLable = new QLabel(tr("Options of current plot"));
    mainlayout->addWidget(optionsLable);
    QPushButton *currentPlotOptions = new QPushButton("Options");
    mainlayout->addWidget(currentPlotOptions);
    connect(currentPlotOptions, SIGNAL(clicked()), this, SLOT(options()));

    setLayout(mainlayout);
}

void PlotChoiseOptionsDialog::options()
{
    static_cast<PlotChoise*>(parent())->optionsCurrentPlot(currentPlot.currentText());
}
