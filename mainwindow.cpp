#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "visual_model.h"
#include "instrument_model.h"
#include "naming_model.h"
#include "manager.h"
#include "colordelegate.h"
#include "comboboxdelegate.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView_3->setItemDelegateForColumn(4, new ColorDelegate());
    ui->tableView_3->setItemDelegateForColumn(2, new ComboBoxDelegate({"square", "circle"}));
    ui->tableView_3->setItemDelegateForColumn(3, new ComboBoxDelegate({"Solid", "something"}));
    ui->tableView_3->setModel(new VisualModel);
    ui->tableView_3->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->tableView_5->setItemDelegateForColumn(0, new ComboBoxDelegate({"relative", "absolute", "calculated"}));
    ui->tableView_5->setModel(new InstrumentModel);
    ui->tableView_5->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->tableView_4->setModel(new NamingModel);
    ui->tableView_4->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

MainWindow::~MainWindow()
{
    delete ui;
}
