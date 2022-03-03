#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "generatekeys.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString text = QString::fromStdString("30");
    ui->textEdit->setText(text);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    std::string bitSize = ui->textEdit->toPlainText().toStdString();
    GenerateKeys* gKey = new GenerateKeys(std::stoul(bitSize));

    try {
        auto [e, s, n] = gKey->generate();

        auto res = gKey->modularExponentation(10, e, n);

        auto res2 = gKey->modularExponentation(res, s,n);

        Utils::writeKeys(e,s,n);

        std::string text = "Public key: [" + std::to_string(e) + " " + std::to_string(n) + "]";

        Utils::addText(ui->listWidget, text);

        text = "Private key: [" + std::to_string(s) + " " + std::to_string(n) + "]";

        Utils::addText(ui->listWidget, text);

    }  catch (const std::exception &ex) {
        std::cout << ex.what() << std::endl;
    }

//    GenerateKeys* gKey = new GenerateKeys(16);

//    try {
//           long value = gKey->modularLinearEquationSolver(491, 1, 540);
//            std::cout << "Value= " << value << std::endl;

//    }  catch (int e) {
//        switch (e) {
//            case 1:
//                std::cout << "Wrong d" << std::endl;
//            break;
//        case 2:
//            std::cout << "No solution" << std::endl;
//        }
//    }





//    long p = 98;
//    long q = 35;

//    long fn = (p-1)*(q-1);



////    long d;
////    long x;
////    long y;
//    //gKey->extendedEuclid(a,b,d,y,x);

//    auto [d, x, y] = gKey->extendedEuclidIterative(p,q);

//    std::cout<< "d= " << d << " x= " << x << " y= " << y <<std::endl;

//    long number = gKey->eNumber(fn);
//    std::cout << "e= " << number << std::endl;
    //std::cout << "a=" << a << " b=" << b << " d=" << d << " x=" << x << " y=" << y<< std::endl;
}


void MainWindow::on_pushButton_2_clicked()
{
    std::string fileToEncrypt = QFileDialog::getOpenFileName(this, tr("File to encrypt"), tr( "/home/david"), tr("All files (*.*)")).toStdString();

    //Utils::addText(ui->listWidget, fileToEncrypt);
    if (fileToEncrypt.empty()) {
        return;
    }

    std::string filePoblicKey = QFileDialog::getOpenFileName(this, tr("Key to encrypt"), tr( "/home/david"), tr("Key files (*.key)")).toStdString();

    if (filePoblicKey.empty()) {
        return;
    }

    auto[e,n] = Utils::readKey(filePoblicKey);

    std::string text = "Public key: [" + std::to_string(e) + " " + std::to_string(n) + "]";

            Utils::addText(ui->listWidget, text);
}


void MainWindow::on_pushButton_3_clicked()
{
    std::string fileToDecrypt = QFileDialog::getOpenFileName(this, tr("File to encrypt"), tr( "/home/david"), tr("All files (*.*)")).toStdString();

    //Utils::addText(ui->listWidget, fileToEncrypt);
    if (fileToDecrypt.empty()) {
        return;
    }

    std::string filePoblicKey = QFileDialog::getOpenFileName(this, tr("Key to encrypt"), tr( "/home/david"), tr("Key files (*.key)")).toStdString();

    if (filePoblicKey.empty()) {
        return;
    }
}

