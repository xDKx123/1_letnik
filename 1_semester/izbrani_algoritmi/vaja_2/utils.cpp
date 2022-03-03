#include "utils.h"

Utils::Utils() : currentStatus(1)
{

}

long Utils::random(long min, long max) {
    long seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::minstd_rand0 generator (seed);

    //currentStatus = LCG((unsigned long)UINT32_MAX +1, 69069, 0, currentStatus);
    //return min + currentStatus % (max - min + 1);
    return min + generator() % (max - min + 1);
}

long Utils::LCG(long m, long a, long b, long r0) {
    return (long)((a*r0 + b ) % m);
}

void Utils::addText(QListWidget *listWidget, std::string text) {
    QString item = QString::fromStdString(text);

    listWidget->addItem(item);

    listWidget->scrollToBottom();
}

void Utils::writeKeys(long e, long s, long n) {
    try {


    std::ofstream fs;
    fs.open(Configuration::publicKeyFileName);
    if (fs.is_open()) {
        //fs << e;
        //fs << n;

        fs.write((char*)&e, sizeof(long));
        fs.write((char*)&n, sizeof(long));


        fs.close();
    }
    else {
        throw 1;
    }
    fs.open(Configuration::privateKeyFileName);
    if (fs.is_open()) {
        //fs << s;
        //fs << n;
        fs.write((char*)&s, sizeof(long));
        fs.write((char*)&n, sizeof(long));

        fs.close();
    }
    else {
        throw 2;
    }

    }  catch (int e) {
        switch (e) {
            case 1:
                std::cout << "Failed 1" << std::endl;
            break;
        case 2:
            std::cout << "Failed 2" << std::endl;
            break;

        }
    }
}

std::tuple<long, long> Utils::readKey(std::string fileName) {
    std::ifstream ifs;
    ifs.open(fileName);

    if (ifs.is_open()) {
        long s;
        long n;

        ifs.read((char*)&s, sizeof(long));
        ifs.read((char*)&n, sizeof(long));

        ifs.close();

        return {s, n};
    }
    throw 1;
}

std::vector<long> Utils::fileContent(std::string fileName, unsigned long readBits) {
    std::fstream fs;
    fs.open(fileName, std::ios::binary);

   std::vector<long> context;
    if (fs.is_open()) {
        std::vector<char> content;

        std::string binaryString = "";
        char c;
        while (fs.get(c)) {
            for (int i = 7; i >= 0; i--)  {
                //content.push_back((c >> i) & 1);
                binaryString.push_back((c >> i) & 1 ? '1' : '0');

                if (binaryString.length() == readBits) {
                    context.push_back(std::bitset<64>(binaryString).to_ulong());
                    binaryString = "";
                }
            }

        }

        if (!binaryString.empty()) {
            context.push_back(std::bitset<64>(binaryString).to_ulong());
        }

        return context;
    }

    throw 1;
}
