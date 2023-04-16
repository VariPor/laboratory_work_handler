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
    void on_open_as_action_triggered();
    void draw();
    void plotOptions();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
