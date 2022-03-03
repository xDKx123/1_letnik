#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

#include <filesystem>
#include <vector>
#include <random>
#include <chrono>

#include "utils.h"
#include "simplex.h"

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
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;

    Simplex *simplex = new Simplex();

    std::vector<std::vector<double>> matrix;
    std::vector<double> bT, cT;
};
#endif // MAINWINDOW_H
