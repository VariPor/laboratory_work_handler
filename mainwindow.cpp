#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "visual_model.h"
#include "instrument_model.h"
#include "naming_model.h"
#include "manager.h"
#include "colordelegate.h"
#include "comboboxdelegate.h"
#include "measurement_model.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Manager::instance()->addVariable(VariableData{"foo", "bar", {1.2, 15.4,111,1112.1}});
    Manager::instance()->addVariable(VariableData{"meh", "ce", {1.2,1}});

    ui->variable_tableView->setModel(new MeasurementModel);
    ui->variable_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->visual_tableView->setItemDelegateForColumn(4, new ColorDelegate);
    ui->visual_tableView->setItemDelegateForColumn(2, new ComboBoxDelegate({"square", "circle"}));
    ui->visual_tableView->setItemDelegateForColumn(3, new ComboBoxDelegate({"solid", "something"}));
    ui->visual_tableView->setModel(new VisualModel);
    ui->visual_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->instruments_tableView->setItemDelegateForColumn(0, new ComboBoxDelegate({"relative", "absolute", "calculated"}));
    ui->instruments_tableView->setModel(new InstrumentModel);
    ui->instruments_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->naming_tableView->setModel(new NamingModel);
    ui->naming_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

MainWindow::~MainWindow()
{
    delete ui;
}
