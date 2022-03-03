#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
    for (int x = 0; x < argc; x++) {
        std::cout << argv[x] << std::endl;
    }

    std::string path = argv[1];

    std::string baseFile = path.substr(path.find_last_of("/\\") + 1 );

    std::cout << baseFile << std::endl;
    
    return 0;
}