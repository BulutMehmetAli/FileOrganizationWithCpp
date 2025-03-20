#include <iostream>
#include <fstream>
using namespace std;

int main() {
    // Writing to a file
    fstream outFile;
    outFile.open("test.txt", ios::out);
    if (!outFile) {
        cout << "File cannot be created!" << endl;
        return 1;
    }
    outFile << "Hello, this is not my first file." << endl;
    outFile << "My name is Mehmet Ali Bulut." << endl;
    outFile << "I am a third-year Computer Engineering student." << endl;
    outFile.close();

    // Reading from a file using getline
    ifstream readFile;
    readFile.open("test.txt", ios::in);
    string line;
    while (getline(readFile, line)) {
        cout << line << endl;
    }
    readFile.close();

    // Reading character by character from "account.txt"
    char c;
    ifstream infile;
    infile.open("account.txt", ios::in);
    infile.unsetf(ios::skipws);
    infile >> c;
    while (!infile.fail()) {
        cout << c;
        infile >> c;
    }
    infile.close();

    // Reading using read() function
    char buffer[100];
    fstream infile2;
    infile2.open("account.txt", ios::in);
    infile2.unsetf(ios::skipws);
    infile2.read(&c, 1);  // Reads 1 byte from the file into 'c'
    infile2.read(buffer, 10);  // Reads 10 bytes from the file into 'buffer'
    infile2.close();

    // Writing using write() function
    fstream outfile;
    outfile.open("account.txt", ios::out);
    outfile.unsetf(ios::skipws);
    outfile << c;
    outfile.write(&c, 1); // Writes 1 byte to the file
    outfile.write(buffer, 10); // Writes 10 bytes from 'buffer'
    outfile.close();

    // Using seekp to move the file pointer
    fstream fileOut("test.txt", ios::out);
    fileOut << "Mehmet Ali Bulut\n";
    fileOut << "Life is good\n";
    fileOut << "Everything is ok\n";
    fileOut.seekp(0, ios::beg); // Move pointer to the beginning
    fileOut << "This is a new text\n"; // Overwrites from the start
    fileOut.close();
    cout << "File updated\n";

    // Using seekg to move the read pointer
    fstream oiFile("example.txt", ios::out | ios::in);
    oiFile << "Computerisgood\n";
    oiFile << 34 << endl;
    oiFile << 78.19 << endl;
    oiFile.clear();
    oiFile.seekg(3, ios::beg);
    cout << "Current pointer position: " << oiFile.tellg() << endl;
    oiFile.seekg(5, ios::cur);
    char str[40];
    int age;
    float weight;
    oiFile >> str;
    oiFile >> age;
    oiFile >> weight;
   // cout << str << "\n" << age << "\n" << weight << "\n";
    oiFile.close();

    // Detecting end of file (EOF)
    ifstream fileCheck("account.txt");
    char tempChar;
    fileCheck >> tempChar;
    if (fileCheck.fail()) { // Checks if EOF is reached
        cout << "End of file reached!" << endl;
    }
    fileCheck.close();

    return 0;
}
