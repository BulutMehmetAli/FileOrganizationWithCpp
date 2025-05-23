#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

// Set the maximum number of elements allowed in the buffer
const int BUFFER_LIMIT = 3;

// In-memory buffer to temporarily store user input
vector<string> buffer;

// Function to write the contents of the buffer to disk
void flushBufferToDisk() {
    ofstream diskFile("disk.txt", ios::app); // Open file in append mode
    if (!diskFile.is_open()) {
        cerr << "Failed to open disk.txt for writing.\n";
        return;
    }

    cout << "\nFlushing buffer to disk...\n";
    for (const string& data : buffer) {
        diskFile << data << endl;
    }
    buffer.clear(); // Clear the buffer after flushing
    cout << "Flush complete.\n\n";
}

// Function to add data to the buffer and flush if full
void addToBuffer(const string& data) {
    buffer.push_back(data);
    cout << "Added to buffer: " << data << endl;

    if (buffer.size() == BUFFER_LIMIT) {
        flushBufferToDisk(); // Auto-flush when buffer is full
    }
}

int main() {
    string value;

    // Clear previous file contents at the start
    ofstream clearFile("disk.txt", ios::out);
    clearFile.close();

    cout << "Buffer Manager Simulation Started\n";
    cout << "Commands:\n";
    cout << " - Enter any string to store it in the buffer\n";
    cout << " - Type 'flush' to manually write buffer to disk\n";
    cout << " - Type 'exit' to quit the program\n\n";

    while (true) {
        cout << "🔸 Enter a string: ";
        cin >> value;  // If you want full sentences, change to getline(cin, value)

        if (value == "exit") {
            if (!buffer.empty()) {
                flushBufferToDisk(); // Final flush before exiting
            }
            cout << "Program terminated.\n";
            break;
        } else if (value == "flush") {
            flushBufferToDisk(); // Manual flush
        } else {
            addToBuffer(value); // Add regular input to buffer
        }
    }

    return 0;
}
