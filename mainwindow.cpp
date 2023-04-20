#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "models/visual_model.h"
#include "models/instrument_model.h"
#include "models/naming_model.h"
#include "models/colordelegate.h"
#include "models/comboboxdelegate.h"
#include "models/measurement_model.h"
#include "manager.h"
#include "strategy_io.h"
#include "plots/plot_hist.h"
#include "plots/plot_scatter.h"
#include "plots/plot_2d.h"
#include "plots/plot_choise.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Manager::instance()->addVariable(VariableData{"meh", "brah", {1,2,3,4,4}});
    Manager::instance()->addVariable(VariableData{"foo", "ohh", {1,2,3,4,5}});

    ui->variable_tableView->setModel(new MeasurementModel);
    ui->variable_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->visual_tableView->setItemDelegateForColumn(4, new ColorDelegate);
    ui->visual_tableView->setItemDelegateForColumn(2, new ComboBoxDelegate(VariableData::VisualOptions::point_types.values()));
    ui->visual_tableView->setItemDelegateForColumn(3, new ComboBoxDelegate(VariableData::VisualOptions::line_types.values()));
    ui->visual_tableView->setModel(new VisualModel);
    ui->visual_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->instruments_tableView->setItemDelegateForColumn(0, new ComboBoxDelegate(VariableData::Instrument::error_types.values()));
    ui->instruments_tableView->setModel(new InstrumentModel);
    ui->instruments_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->naming_tableView->setModel(new NamingModel);
    ui->naming_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    Manager::instance()->plot = new PlotChoise({
                                                    {"Scatter plot", new PlotScatter},
                                                    {"Histogram plot", new PlotHistogram},
                                                    {"2d scatter plot", new Plot2d("",
                                                                                   "")}
                                                });
    Manager::instance()->plot->draw(ui->plot);

    connect(ui->actionReplot, SIGNAL(triggered()), this, SLOT(draw()));
    connect(ui->actionOptions, SIGNAL(triggered()), this, SLOT(plotOptions()));
    connect(ui->actionOpenAs, SIGNAL(triggered()), this, SLOT(openFile()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::draw()
{
    Manager::instance()->plot->draw(ui->plot);
}

void MainWindow::plotOptions()
{
    Manager::instance()->plot->options();
}

void MainWindow::openFile()
{
    QString str = QFileDialog::getOpenFileName(0, "Открыть", "", "*.csv");
    if (str.isEmpty()) return;
    StrategyIO_CSV loader;
    loader.load(str);
    ui->variable_tableView->model()->deleteLater();
    ui->variable_tableView->setModel(new MeasurementModel);
    ui->visual_tableView->setModel(new VisualModel);
    ui->instruments_tableView->setModel(new InstrumentModel);
    ui->naming_tableView->setModel(new NamingModel);
}

