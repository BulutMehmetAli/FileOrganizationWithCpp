#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

// Actual record structure
struct Record {
    string company;
    string id;
    string title;
    string category;
    int year;
};

// Structure to be written to the index file: key + byte address
struct IndexEntry {
    string key;            // company + id
    streampos address;     // byte offset in records.txt
};

// Comparator for sorting by key
bool compareByKey(const IndexEntry& a, const IndexEntry& b) {
    return a.key < b.key;
}

// Write records to disk and simultaneously create the index array
void writeRecordsToDisk(const vector<Record>& records, const string& filename, vector<IndexEntry>& indexArray) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error: Unable to open " << filename << " for writing.\n";
        return;
    }

    for (const auto& rec : records) {
        streampos addr = outFile.tellp(); // Current file position
        string key = rec.company + rec.id;
        indexArray.push_back({key, addr}); // Add to index array

        outFile << rec.company << " | " << rec.id << " | " << rec.title << " | "
                << rec.category << " | " << rec.year << "\n";
    }

    outFile.close();
    cout << "Records written to '" << filename << "'.\n";
}

// Write the index file
void writeIndexToFile(const vector<IndexEntry>& indexArray, const string& filename) {
    ofstream idxFile(filename);
    if (!idxFile) {
        cerr << "Error: Unable to open " << filename << " for writing.\n";
        return;
    }

    idxFile << "KEY\t\tADDRESS\n";
    idxFile << "---------------------------\n";
    for (const auto& entry : indexArray) {
        idxFile << entry.key << "\t" << entry.address << "\n";
    }

    idxFile.close();
    cout << "Index written to '" << filename << "'.\n";
}
void searchRecord(const vector<IndexEntry>& indexArray, const string& recordFile) {
    string inputKey;
    cout << "\nEnter the key to search (e.g., ANG3795): ";
    cin >> inputKey;

    auto it = find_if(indexArray.begin(), indexArray.end(), [&](const IndexEntry& e) {
        return e.key == inputKey;
    });
    ifstream inFile(recordFile);
    if (!inFile) {
        cerr << "Error: Unable to open " << recordFile << " for reading.\n";
        return;
    } else {
        if (it != indexArray.end()) {
            inFile.seekg(it->address); // Jump to the address
            string line;
            getline(inFile, line);

            if (getline(inFile, line)) {
                stringstream ss(line);
                string company, id, title, category, year;

                // '|' karakteri ayraç olarak kullanılarak alanları al
                getline(ss, company, '|');
                getline(ss, id, '|');
                getline(ss, title, '|');
                getline(ss, category, '|');
                getline(ss, year);

                // Trim (baş ve sondaki boşlukları temizlemek iyi olur)
                auto trim = [](string& s) {
                    size_t start = s.find_first_not_of(" \t");
                    size_t end = s.find_last_not_of(" \t");
                    if (start == string::npos || end == string::npos) s = "";
                    else s = s.substr(start, end - start + 1);
                };

                trim(company);
                trim(id);
                trim(title);
                trim(category);
                trim(year);

                cout << "\nRecord Found:\n--------------------\n"
                     << "Company: " << company << "\n"
                     << "ID: " << id << "\n"
                     << "Title: " << title << "\n"
                     << "Category: " << category << "\n"
                     << "Year: " << year << "\n";
            } else {
                cout << "Error: Failed to read the line at the given position.\n";
            }
            inFile.close();
        } else {
            cout << "Key not found in index.\n";
        }
    }

}
int main() {
    // Sample dataset
    vector<Record> records = {
        {"LON", "2312", "Symphony N.S.", "Classical", 1980},
        {"RCA", "2626", "Quartet in C sharp", "Chamber", 1975},
        {"WAR", "23699", "Adagio", "Orchestral", 1990},
        {"ANG", "3795", "Violin Concerto", "Romantic", 1985}
    };

    vector<IndexEntry> indexArray;

    // 1. Write records to disk and create the index array
    writeRecordsToDisk(records, "records.txt", indexArray);

    // 2. Sort the index array
    sort(indexArray.begin(), indexArray.end(), compareByKey);

    // 3. Create the index file
    writeIndexToFile(indexArray, "index.txt");

    // 4. Perform search
    searchRecord(indexArray, "records.txt");

    cout << "\nProgram ended.\n";
    return 0;
}
