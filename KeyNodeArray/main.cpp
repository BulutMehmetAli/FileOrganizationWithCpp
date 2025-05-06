#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

// Gerçek kaydın yapısı
struct Record {
    string name;
    string address;
};

// Sadece key ve RRN içeren yapı
struct KeyNode {
    string key;
    int rrn;
};

bool compare(KeyNode a, KeyNode b) {
    return a.key < b.key;
}
int main() {
    // Diskteki kayıtlar (simülasyon)
    vector<Record> records = {
        {"HARRISON", "387 Eastern"},
        {"KELLOG", "17 Maple"},
        {"HARRIS", "4343 West"},
        {"BELL", "8912 Hill"}
    };

    vector<KeyNode> indexArray;
    for (int i = 0; i < records.size(); ++i) {
        indexArray.push_back({records[i].name, i}); // key = name, RRN = index
    }
    sort(indexArray.begin(), indexArray.end(), compare);

    ofstream indexFile("index.txt");

    if (!indexFile.is_open()) {
        cerr << "Failed to create index file.\n";
        return 1;
    }
    indexFile << "Key\tRRN\n";
    indexFile << "--------------\n";
    for (const auto& record : indexArray) {
        indexFile << record.key << " \t" << record.rrn << "\n";
    }
    indexFile.close();
    cout << "✅ Index file 'index.txt' created successfully.\n";

    return 0;
}
