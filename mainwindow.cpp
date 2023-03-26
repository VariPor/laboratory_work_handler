#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tables.h"
#include "manager.h"
#include "colordelegate.h"
#include "comboboxdelegate.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    Manager::instance()->addVariable(VariableData("bee"));

    ui->setupUi(this);
    ui->tableView_3->setItemDelegateForColumn(4, new ColorDelegate());
    ui->tableView_3->setItemDelegateForColumn(2, new ComboBoxDelegate({"square", "circle"}));
    ui->tableView_3->setItemDelegateForColumn(3, new ComboBoxDelegate({"solid", "something"}));
    ui->tableView_3->setModel(new VisualModel);
    ui->tableView_3->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

MainWindow::~MainWindow()
{
    delete ui;
}

