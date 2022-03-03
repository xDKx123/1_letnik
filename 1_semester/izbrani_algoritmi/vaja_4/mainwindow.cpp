#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    try {

        std::string fileName = QFileDialog::getOpenFileName(this, tr("Open file"), "/home/david/Desktop/School/1_letnik/izbrani_algoritmi/vaja_4", tr("Text files (*.txt)")).toStdString();

        if (fileName.empty()) {
            return;
        }

        auto [n,m, tmp_matrix, tmp_bT, tmp_cT] = Utils::readFile(fileName);

        delete simplex;

        simplex = new Simplex(n,m);
        matrix = tmp_matrix;
        bT = tmp_bT;
        cT= tmp_cT;

    }  catch (const std::exception& ex) {
        Utils::addTextListWidget(ui->listWidget, ex.what());
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->listWidget->clear();

    try {
        auto [res, z] = simplex->algorithm(matrix, bT, cT);

        std::string text = "";
        for (unsigned int x = 0; x < res.size(); x++) {
            text += "x[" + std::to_string(x+1) + "]: " + std::to_string(res[x]) + "\n";
        }
        text+= "\nz: " + std::to_string(z);

        Utils::addTextListWidget(ui->listWidget, text);

    }  catch (const std::string &ex) {
        Utils::addTextListWidget(ui->listWidget, ex);
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    ui->progressBar->setValue(0);

    srand(time(NULL));

    const int maxMatrixSize = 15;
    const int maxNumberOfTryes = 100000;

    std::ofstream of;
    of.open("testing.txt");

    of << "n = m" << "\t" << "Average" << "\t" << "Smallest time" << "\t" << "BiggestTime" << std::endl;

    auto startTesting = std::chrono::system_clock::now();

    for (int x = 2; x < maxMatrixSize; x++) {

        std::vector<unsigned long> timesFirst;

        for (int y = 0; y < maxNumberOfTryes; y++) {
            delete simplex;
            simplex = new Simplex(x,x);
            matrix = Utils::random2Dmatrix(x*2);
            bT = Utils::random1Dmatrix(x*2);
            cT= Utils::random1Dmatrix(x*2);

            auto start = std::chrono::system_clock::now();

            try {
                simplex->algorithm(matrix, bT, cT);
            }  catch (const std::string &ex) {
                //Utils::addTextListWidget(ui->listWidget, ex);
            }

            auto end = std::chrono::system_clock::now();

            auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

            timesFirst.push_back(time);
        }

        double avgTime = (double)std::accumulate(timesFirst.begin(), timesFirst.end(), 0) / timesFirst.size();
        double smallestTime = *std::min_element(timesFirst.begin(), timesFirst.end());
        double biggestTime = *std::max_element(timesFirst.begin(), timesFirst.end());

        of << x << "\t" << avgTime << "\t" << smallestTime << "\t" << biggestTime << std::endl;

        ui->progressBar->setValue((double)(x-1) / (maxMatrixSize - 2)*100);
    }

    auto endTesting = std::chrono::system_clock::now();

    auto timeTesting = std::chrono::duration_cast<std::chrono::seconds>(endTesting - startTesting).count();

    Utils::addTextListWidget(ui->listWidget, "Finished in: " + std::to_string(timeTesting) + " sec.");


    of.close();
}

