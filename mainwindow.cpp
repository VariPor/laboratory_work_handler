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
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveFile()));
    connect(ui->actionOpen_directory, SIGNAL(triggered()), this, SLOT(openDirectory()));
    connect(ui->actionSave_to_directory, SIGNAL(triggered()), this, SLOT(saveDirectory()));
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
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "data.csv",
                                                    tr("Open CSV (*.csv);;Open json (*.json)"));

    if (fileName.isEmpty()) return;
    if (fileName.endsWith(".csv")) {
        Manager::instance()->clear();
        StrategyIO_CSV loader;
        loader.load(fileName);
    }
    if (fileName.endsWith(".json")) {
        StrategyIO_JSON loader;
        loader.load(fileName);
    }

    ui->variable_tableView->model()->deleteLater();
    ui->variable_tableView->setModel(new MeasurementModel);
    ui->visual_tableView->setModel(new VisualModel);
    ui->instruments_tableView->setModel(new InstrumentModel);
    ui->naming_tableView->setModel(new NamingModel);
}

void MainWindow::saveFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "data.csv",
                                                    tr("Open CSV (*.csv);;Open json (*.json)"));
    if (fileName.endsWith(".csv")) {
        StrategyIO_CSV saver;
        saver.save(fileName);
    }
    if (fileName.endsWith(".json")) {
        StrategyIO_JSON saver;
        saver.save(fileName);
    }
}

void MainWindow::openDirectory(){
    auto dirName = QFileDialog::getExistingDirectory(this, tr("Open directory"), "",
                                                     QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    QString file_csv = dirName + QDir::separator() + "data.csv";
    QString file_json = dirName + QDir::separator() + "data.json";

    //Manager::instance()->clear();

    StrategyIO_CSV loader_csv;
    loader_csv.load(file_csv);

    StrategyIO_JSON loader_json;
    loader_json.load(file_json);

    ui->variable_tableView->model()->deleteLater();
    ui->variable_tableView->setModel(new MeasurementModel);
    ui->visual_tableView->setModel(new VisualModel);
    ui->instruments_tableView->setModel(new InstrumentModel);
    ui->naming_tableView->setModel(new NamingModel);
}

void MainWindow::saveDirectory()
{
    auto dirName = QFileDialog::getExistingDirectory(this, tr("Open directory"), "",
                                                     QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    QString file_csv = dirName + QDir::separator() + "data.csv";
    QString file_json = dirName + QDir::separator() + "data.json";

    StrategyIO_CSV saver_csv;
    saver_csv.save(file_csv);

    StrategyIO_JSON saver_json;
    saver_json.save(file_json);
}
