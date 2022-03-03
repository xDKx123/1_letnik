#include "utils.h"

Utils::Utils()
{

}

std::tuple<int, int, std::vector<std::vector<double>>, std::vector<double>, std::vector<double>> Utils::readFile(std::string fileName) {
    std::fstream fs;
    fs.open(fileName);

    if (fs.bad()) {
        throw "File not found";
    }

    try {
        int n,m;

        fs >> n;
        fs >> m;

        std::vector<std::vector<double>> matrix;
        for (int x = 0; x < m+n; x++) {
            std::vector<double> v;
            for (int y = 0; y < m+n; y++) {
                int i;

                fs >> i;

                v.push_back((double)i);
            }
            matrix.push_back(v);
        }

        std::vector<double> bT;

        for (int x = 0; x < m+n; x++) {
            int i;

            fs >> i;

            bT.push_back((double)i);
        }

        std::vector<double> cT;

        for (int x = 0; x < m+n; x++) {
            int i;

            fs >> i;

            cT.push_back((double)i);
        }

        return {n,m, matrix, bT, cT};

    }  catch (const std::exception& ex) {
        throw ex;
    }
}

void Utils::addTextListWidget(QListWidget *listWidget, std::string text) {
    QString item = QString::fromStdString(text);

    listWidget->addItem(item);

    listWidget->scrollToBottom();
}



std::vector<std::vector<double>> Utils::copy2Dmatrix(std::vector<std::vector<double>> matrix) {
    std::vector<std::vector<double>> newMatrix;

    for (auto column : matrix) {
        std::vector<double> v;
        for (auto cel : column) {
            v.push_back(cel);
        }
        newMatrix.push_back(v);
    }

    return newMatrix;
}


std::vector<double> Utils::copy1Dmatrix(std::vector<double> matrix) {
    std::vector<double> newMatrix;

    for (auto cel : matrix) {
        newMatrix.push_back(cel);
    }

    return newMatrix;
}

std::vector<int> Utils::copy1Dmatrix(std::vector<int> matrix) {
    std::vector<int> newMatrix;

    for (auto cel : matrix) {
        newMatrix.push_back(cel);
    }

    return newMatrix;
}

std::vector<std::vector<double>> Utils::empty2Dmatrix(std::vector<std::vector<double>> matrix) {
    std::vector<std::vector<double>> newMatrix;

    for (auto column : matrix) {
        std::vector<double> v;
        for (auto cel : column) {
            v.push_back(0);
        }
        newMatrix.push_back(v);
    }

    return newMatrix;
}


std::vector<double> Utils::empty1Dmatrix(std::vector<double> matrix) {
    std::vector<double> newMatrix;

    for (auto cel : matrix) {
        newMatrix.push_back(0.0);
    }

    return newMatrix;
}

std::vector<int> Utils::empty1Dmatrix(std::vector<int> matrix) {
    std::vector<int> newMatrix;

    for (auto cel : matrix) {
        newMatrix.push_back(0);
    }

    return newMatrix;
}

std::vector<std::vector<double>> Utils::random2Dmatrix(unsigned int size) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(-1000,1000); // distribution in range [-1000, 1000]

    std::vector<std::vector<double>> newMatrix;

    for (unsigned int x = 0; x < size; x++) {
        std::vector<double> v;
        for (unsigned int y = 0; y < size; y++) {
            v.push_back(dist(rng));
        }
        newMatrix.push_back(v);
    }

    return newMatrix;

}
std::vector<double> Utils::random1Dmatrix(unsigned int size) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0,2000); // distribution in range [-1000, 1000]

    std::vector<double> newMatrix;

    for (unsigned int x = 0; x < size; x++) {
        newMatrix.push_back(dist(rng));
    }

    return newMatrix;

}
