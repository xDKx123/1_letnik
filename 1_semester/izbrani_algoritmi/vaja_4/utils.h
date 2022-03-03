#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <tuple>
#include <random>

#include <QListWidget>

class Utils
{
public:
    Utils();

    static std::tuple<int, int, std::vector<std::vector<double>>, std::vector<double>, std::vector<double>> readFile(std::string fileName);
    static void addTextListWidget(QListWidget *listWidget, std::string text);

    static std::vector<std::vector<double>> copy2Dmatrix(std::vector<std::vector<double>> matrix);
    static std::vector<double> copy1Dmatrix(std::vector<double> matrix);
    static std::vector<int> copy1Dmatrix(std::vector<int> matrix);

    static std::vector<std::vector<double>> empty2Dmatrix(std::vector<std::vector<double>> matrix);
    static std::vector<double> empty1Dmatrix(std::vector<double> matrix);
    static std::vector<int> empty1Dmatrix(std::vector<int> matrix);


    static std::vector<std::vector<double>> random2Dmatrix(unsigned int size);
    static std::vector<double> random1Dmatrix(unsigned int size);

};

#endif // UTILS_H
