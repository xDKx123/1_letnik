#include "mainwindow.h"
#include "ui_mainwindow.h"

unsigned long randomNumber;
int maxBitNumber;
Utils *utils = new Utils();

void writeListViewProgress(std::string text, Ui::MainWindow *ui) {
    QString item = QString::fromStdString(text);

    ui->listWidget->addItem(item);
    ui->listWidget->scrollToBottom();
}

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
    //std::cout << "Print" << std::endl;
    BruteForce* bf = new BruteForce();

    long number = bf->algorithm(randomNumber);

    std::string text = std::to_string(number) + " is primer number.";

    QString item = QString::fromStdString(text);

    ui->listWidget->addItem(item);

    delete bf;
}


void MainWindow::on_pushButton_2_clicked()
{
    int s = ui->textEdit_2->toPlainText().toInt();
    MillerRabin *mr = new MillerRabin();

    long number = mr->algorithm(maxBitNumber, randomNumber, s, utils);

    std::string text = std::to_string(number) + " is primer number.";

    QString item = QString::fromStdString(text);


    ui->listWidget->addItem(item);
    delete mr;

}


void MainWindow::on_pushButton_3_clicked()
{
    maxBitNumber = ui->textEdit->toPlainText().toInt();
    randomNumber = utils->random(0, pow(2, maxBitNumber));

    std::string text = "New generated number: " + std::to_string(randomNumber);
    QString item = QString::fromStdString(text);

    ui->listWidget->addItem(item);
    ui->listWidget->scrollToBottom();

}


void MainWindow::on_pushButton_4_clicked()
{
    const std::string outFile = "outTestingAlgorithms.txt";

    std::fstream fs(outFile, std::fstream::out);

    if (!fs.is_open()) {
        writeListViewProgress("fileNotFound", ui);
        return;
    }

    MillerRabin *mr = new MillerRabin();
    BruteForce* bf = new BruteForce();
    try {

        for (int x = 4; x <= 32; x++) {
            unsigned long min = pow(2,x-1);
            unsigned long max = pow(2, x)-1;

            std::vector<unsigned long> timesFirst;
            std::vector<unsigned long> timesSeccond;

            for (int y = 0; y < 1000; y++) {

                unsigned long randNum = utils->random(min, max);

                auto start = std::chrono::system_clock::now();

                mr->algorithm(x, randNum, 2, utils);

                auto end = std::chrono::system_clock::now();

                auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

                timesFirst.push_back(time);


                start = std::chrono::system_clock::now();

                bf->algorithm(randNum);

                end = std::chrono::system_clock::now();

                time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

                timesSeccond.push_back(time);
            }

            double avgTimeFirst = (double)std::accumulate(timesFirst.begin(), timesFirst.end(), 0) / timesFirst.size();
            double avgTimeSeccond = (double)std::accumulate(timesSeccond.begin(), timesSeccond.end(), 0) / timesSeccond.size();
            fs << x << " " << avgTimeFirst << " " << avgTimeSeccond << std::endl;
            ui->progressBar->setValue(((double)(x-4) / (32-4))*100);

            //mr->algorithm(x, min, 2);
            //bf->algorithm(x);

        }

    }  catch (const std::exception e) {
        writeListViewProgress(e.what(), ui);
    }


    fs.close();
    delete mr;
    delete bf;

}


void MainWindow::on_pushButton_5_clicked()
{
    const std::string outFile = "outTestingS.txt";

    std::fstream fs(outFile, std::fstream::out);

    if (!fs.is_open()) {
        writeListViewProgress("fileNotFound", ui);
        return;
    }


    ui->progressBar->setValue(0);
    MillerRabin *mr = new MillerRabin();
    try {
        unsigned long min = pow(2,32-1);
        unsigned long max = pow(2, 32)-1;

        unsigned long randNum = utils->random(min, max);

        for (int x = 1; x <= 20; x++) {
            //writeListViewProgress(std::to_string(x), ui);

            std::vector<unsigned long> times;
            for (int y = 0; y < 1000; y++) {



                auto start = std::chrono::system_clock::now();

                mr->algorithm(32, randNum,x, utils);

                auto end = std::chrono::system_clock::now();

                auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

                times.push_back(time);
            }

            double avgTime = (double)std::accumulate(times.begin(), times.end(), 0) / times.size();
            fs << x << " " << avgTime << std::endl;

            ui->progressBar->setValue(((double)(x-1) / (20-1))*100);
        }

    }  catch (const std::exception e) {
        writeListViewProgress(e.what(), ui);
    }

    fs.close();
    delete mr;
}

