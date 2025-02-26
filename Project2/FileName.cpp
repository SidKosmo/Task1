#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>
#include <filesystem>

using namespace std;

vector<unsigned char> readFile(const string& filename, streamsize& fileSize) {
    ifstream file(filename, ios::binary);
    fileSize = filesystem::file_size(filename);
    vector<unsigned char> buffer(fileSize);
    file.read(reinterpret_cast<char*>(buffer.data()), fileSize);
    return buffer;
}

double calculateEntropy(const vector<unsigned char>& bytes) {
    map<unsigned char, size_t> byteCounts;
    for (unsigned char byte : bytes) byteCounts[byte]++;
    double entropy = 0.0;
    for (const auto& count : byteCounts) {
        double probability = static_cast<double>(count.second) / bytes.size();
        entropy -= probability * log2(probability);
    }
    return entropy;
}

void printByteFrequencyTable(const map<unsigned char, size_t>& byteCounts) {
    vector<pair<unsigned char, size_t>> frequencyTable(byteCounts.begin(), byteCounts.end());
    sort(frequencyTable.begin(), frequencyTable.end(), [](const auto& a, const auto& b) {
        return b.second < a.second;
        });
    cout << "Байт\tЧастота" << endl;
    for (const auto& entry : frequencyTable) {
        cout << static_cast<int>(entry.first) << "\t" << entry.second << endl;
    }
}

int main() {
    system("chcp 1251");
    string filename = "C:\\Users\\Admin\\Desktop\\Арх03\\Текст03.txt";

    streamsize fileSize;
    vector<unsigned char> fileBytes = readFile(filename, fileSize);

    cout << "Размер файла: " << fileSize << " байт" << endl;
    cout << "Энтропия файла: " << calculateEntropy(fileBytes) << " бит/байт" << endl;

    map<unsigned char, size_t> byteCounts;
    for (unsigned char byte : fileBytes) byteCounts[byte]++;
    cout << "\nТаблица частот байтов:" << endl;
    printByteFrequencyTable(byteCounts);

    return 0;
}