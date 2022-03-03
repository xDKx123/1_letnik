#include <iostream>
#include <fstream>
#include <string.h>
#include <fstream>
#include <vector>
#include <chrono>
#include <random>
#include <limits>

typedef std::numeric_limits< double > dbl;
typedef std::numeric_limits<float> flt;

const std::string fileName = "neresljivo.txt";

void print(std::vector<std::vector<double>> matrix) {
    std::cout << std::endl;
    for (unsigned int x = 0; x < matrix.size(); x++) {
        for (unsigned int y = 0; y < matrix[x].size(); y++) {
            if (y == matrix[x].size() -1) {
                std::cout << "|\t";
            }
            std::cout << matrix[x][y] << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


std::vector<double> gaussElemination(std::vector<std::vector<double>> matrix, int n) {
    std::vector<double> result;
    for (unsigned int i = 0; i < n; i++) {
        result.push_back((double)0);
    }


    for (unsigned int k = 0; k < n ; k++) {
        double smallest = matrix[k][k];
        int pos = k;
        for (unsigned int j = k; j < n; j++) {
            if (matrix[j][k] < smallest && matrix[j][k] != (double)0.0) {
                smallest = matrix[j][k];
                pos = j;
            }
        }
        if (smallest == (double)0.0) {
            //throw std::string("a[" + std::to_string(pos) +  "][" + std::to_string(k) + "] incorrect value.");
            throw std::string("Invalid matrix.");
        }
        else {
            double divider = (double)matrix[pos][k];
            for (unsigned int i = 0; i < n+1; i++) {
                //tmp.push_back(matrix[k][i]);
                std::swap(matrix[k][i], matrix[pos][i]);
            }

            for (int i = 0; i < n+1; i++) {
                matrix[k][i] /= divider;
            }
        }


        //print(matrix);

        for (unsigned int l = k+1; l < n; l++) {
            double firstValue = matrix[l][k];
            for (unsigned int i = 0; i <= n; i++) {
                //std::cout << matrix[l][i] << " " << matrix[k][i] << " " << firstValue << std::endl;
                matrix[l][i] -= (matrix[k][i]* firstValue);
            }        
        }

        //print(matrix);
    }

    //print(matrix);


    if (matrix[n-1][n-1] == 0) {
        throw std::string("a[" + std::to_string(n-1) +  "][" + std::to_string(n-1) + "] must be different than 0");
    }

    try {
        result[n-1] = matrix[n-1][n]/(double)matrix[n-1][n-1];

        
        for (int i = n - 2; i >= 0; i--) {
            result[i] = matrix[i][n];
            //std::cout << result[i] << std::endl;
            for (unsigned int j = i+1; j<=n; j++) {
                result[i] = result[i] - matrix[i][j]*result[j];
                //std::cout << result[i] << std::endl;
            }
            result[i] = result[i]/(double)matrix[i][i];
            //std::cout << result[i] << std::endl;
        }
    }
    catch (...) {
        throw std::string("There is no solution");
    }


    return result;
}


void testing() {   
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(-100, 100); // distribution in range [1, 10]

    std::fstream fs("out.txt");

    for (int n = 3; n <= 20; n++) {
        std::vector<std::vector<double>> matrix;

        for (unsigned int x = 0; x < n; x++) {
            std::vector<double> v;
            for (unsigned int y = 0; y <= n; y++) {
                //int i;
                v.push_back(1);
                //v.push_back((double)dist(rng));
            }
            matrix.push_back(v);
        }

        for (unsigned int x = 0; x < n; x++) {
            matrix[x][x]=2;
            matrix[x][n]=(double)dist(rng);
        }
        for (unsigned int x = 0; x < n; x++) {
            for (unsigned int y = x+1; y < n; y++) {
                matrix[x][y] = 0;
            }
        }

        //print(matrix);

        std::vector<long> times;
        for (int x = 0; x < 100000; x++) {
            auto start = std::chrono::system_clock::now();

            try {
                std::vector<double> result = gaussElemination(matrix, n);
            }
            catch (std::string const & ex) {
                std::cerr << ex << std::endl;
            }

            auto end = std::chrono::system_clock::now();

            long time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            times.push_back(time);
        }
        
        long avgTime = std::accumulate(times.begin(), times.end(),0) / times.size();

        std::cout << n << " " << avgTime << std::endl;
        fs << n << " " << avgTime << std::endl;
    }

    fs.close();
}

int main() {
    srand(time(NULL));
    std::cout.precision(dbl::max_digits10);
    //std::cout.precision(flt::max_digits10);

    std::fstream fs(fileName);
    int n;

    fs >> n;

    std::vector<std::vector<double>> matrix;

    for (unsigned int x = 0; x < n; x++) {
        std::vector<double> v;
        for (unsigned int y = 0; y <= n; y++) {
            double i;
            fs >> i;
            v.push_back(i);
        }
        matrix.push_back(v);
    }


    auto start = std::chrono::system_clock::now();

    try {
        std::vector<double> result = gaussElemination(matrix, n);

        auto end = std::chrono::system_clock::now();
        long time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

        for (int el = 0; el < result.size(); el++) {
            std::cout<<"x[" << el  <<"] = "<< result[el]<< std::endl;
        }

        std::cout << "Time: " << time << "ns." << std::endl;
    }
    catch (std::string const & ex) {
        std::cerr << ex << std::endl;
    }


    //testing();

    return 0;
}

//TEST double:
//x[0] = 1;
//x[1] = 1;

//TEST float:
//x[0] = 0;
//x[1] = 1;