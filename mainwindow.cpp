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
#include "editor_odf.h"
#include "qcpdocumentobject.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Manager::instance()->addVariable(VariableData{"foo", "ohh", {6,6.5,6,7,8}});
    Manager::instance()->addCalculated(VariableData{"meh", "brah", {1,2,3,4,4}, {1, 1, 2, 3}});


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

    EditorODF::instance()->createDocument(this);
    ui->ODF_export->setDocument(EditorODF::instance()->getDocument());

    Manager::instance()->plot = new PlotChoise({
                                                    {"Scatter plot", new PlotScatter},
                                                    {"Histogram plot", new PlotHistogram},
                                                    {"2d scatter plot", new Plot2d("", "")}});
    Manager::instance()->plot->draw(ui->plot);

    connect(ui->actionReplot, SIGNAL(triggered()), this, SLOT(draw()));
    connect(ui->actionOptions, SIGNAL(triggered()), this, SLOT(plotOptions()));
    connect(ui->actionOpenAs, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveFile()));
    connect(ui->actionOpen_directory, SIGNAL(triggered()), this, SLOT(openDirectory()));
    connect(ui->actionSave_to_directory, SIGNAL(triggered()), this, SLOT(saveDirectory()));
    connect(ui->actiontext_block, SIGNAL(triggered()), this, SLOT(addText()));
    connect(ui->actiontable_block, SIGNAL(triggered()), this, SLOT(addTable()));
    connect(ui->actionplot_block, SIGNAL(triggered()), this, SLOT(addPlot()));
    connect(ui->actionexport, SIGNAL(triggered()), this, SLOT(exportODF()));
    connect(ui->delete_block, SIGNAL(clicked()), this, SLOT(deleteBlock()));
    connect(ui->ODF_export, SIGNAL(cursorPositionChanged()), this, SLOT(changeCursorPositional()));
    connect(ui->pushButtonColumnAdd, SIGNAL(clicked()), this, SLOT(addVariable()));
    connect(ui->pushButtonRowAdd, SIGNAL(clicked()), this, SLOT(addRow()));
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
    ui->visual_tableView->model()->deleteLater();
    ui->visual_tableView->setModel(new VisualModel);
    ui->instruments_tableView->model()->deleteLater();
    ui->instruments_tableView->setModel(new InstrumentModel);
    ui->naming_tableView->model()->deleteLater();
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

    if (!QFile(file_csv).exists() || !QFile(file_json).exists()) return;

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

void MainWindow::addText() {
    EditorODF::instance()->addTextBlock();
}

void MainWindow::addTable() {
    EditorODF::instance()->addTableBlock();
}

void MainWindow::addPlot() {
    EditorODF::instance()->addPlotBlock(ui->plot);
}

void MainWindow::exportODF() {
    QString fileName = QFileDialog::getSaveFileName(nullptr,QObject::tr("Save File"),"output_file.odf",QObject::tr("Open Document ('''.odf)"));
    QTextDocumentWriter fileWriter (fileName);
    fileWriter.setFormat("odf");
    QTextDocument* doc = EditorODF::instance()->getDocument();
    bool temp = fileWriter.write(doc);
    qInfo() << temp;
}

void MainWindow::deleteBlock() {
    QTextCursor* cursor = EditorODF::instance()->getCursor();
    qInfo() << cursor->position();
    qInfo() << cursor->block().previous().position();
    cursor->setPosition(cursor->block().position());
    qInfo() << cursor->position();

    /*qInfo() << cursor->position();
    cursor->setPosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
    qInfo() << cursor->position();*/
    /*cursor.setPosition(QTextCursor::StartOfBlock);
    qInfo() << cursor.position();*/

    cursor->select(QTextCursor::BlockUnderCursor);
    qInfo() << cursor->position();
    qInfo() << cursor->selectedText();
    cursor->removeSelectedText();
}


void MainWindow::changeCursorPositional() {
    EditorODF::instance()->getCursor()->setPosition(ui->ODF_export->textCursor().position());
}

void MainWindow::addVariable()
{
    auto m = Manager::instance();
    m->addVariable(VariableData{m->getMeasurementsCount()});
    static_cast<MeasurementModel*>(ui->variable_tableView->model())->insertColumn(m->getCalculatedCount());
    static_cast<VisualModel*>(ui->visual_tableView->model())->insertRow(m->getCalculatedCount());
    static_cast<InstrumentModel*>(ui->instruments_tableView->model())->insertRow(m->getCalculatedCount());
    static_cast<NamingModel*>(ui->naming_tableView->model())->insertRow(m->getCalculatedCount());
}

void MainWindow::addRow()
{
    auto m = Manager::instance();
    static_cast<MeasurementModel*>(ui->variable_tableView->model())->insertRow(m->getMeasurementsCount());
}
