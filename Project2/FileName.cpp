#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>
#include <filesystem>

using namespace std;


int main() {
    
    system("chcp 1251");

    string filename = "C:\\Users\\Admin\\Desktop\\Арх03\\Текст03.txt";
    streamsize fileSize;
    ifstream file;
    vector<unsigned char> buffer;
    double entropy = 0.0;
    map<unsigned char, size_t> byteCountsQ;
    //Все переменные.

    file.open(filename, ios::binary);

    fileSize = filesystem::file_size(filename);

    buffer.resize(fileSize);
    file.read(reinterpret_cast<char*>(buffer.data()), fileSize);
    file.close();
    

   
    
    for (unsigned char byte : buffer) byteCountsQ[byte]++;
    
    for (const auto& count : byteCountsQ) {
    double probability = static_cast<double>(count.second) / fileSize;
    entropy -= probability * log2(probability);}
        
    cout << "Размер файла: " << fileSize << " байт" << endl;
    cout << "Энтропия файла: " << entropy << " бит/байт" << endl;


    cout << "\nТаблица частот байтов:" << endl;

    vector<pair<unsigned char, size_t>> frequencyTable(byteCountsQ.begin(), byteCountsQ.end());
    sort(frequencyTable.begin(), frequencyTable.end(), [](const auto& a, const auto& b) {
        return b.second < a.second;
        });
    cout << "Байт\tЧастота" << endl;
    for (const auto& entry : frequencyTable) {
        cout << static_cast<int>(entry.first) << "\t" << entry.second << endl;
    }

    return 0;
}