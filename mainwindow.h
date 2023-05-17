#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "strategy_io.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openFile();
    void saveFile();
    void draw();
    void plotOptions();
    void saveDirectory();
    void openDirectory();
    void addText();
    void addTable();
    void addPlot();
    void exportODF();
    void deleteBlock();
    void moveUpBlock();
    void moveDownBlock();
    void addVariable();
    void addRow();
    void callParser();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
