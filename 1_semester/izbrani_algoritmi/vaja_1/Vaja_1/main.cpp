#include "mainwindow.h"
#include "utils.h"
#include "bruteforce.h"
#include "millerrabin.h"

#include <iostream>

#include <QApplication>

int main(int argc, char *argv[])
{
    //std::cout << Utils::random(100,200) << std::endl;
//    BruteForce* bruteForce = new BruteForce();

//    std::cout << bruteForce->algorithm() << std::endl;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
