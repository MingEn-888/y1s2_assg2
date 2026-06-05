#include <iostream>
#include <vector>
#include <string>
#include "File.h"
#include "Folder.h"
#include "FileSystem.h"
using namespace std;

// ---- input validation in MAIN ----
string readNonEmptyLine(const string& prompt) {
    bool keeprunning = true;
    string line="";
    while (keeprunning) {
        cout << prompt;
        if (!getline(cin, line)) {
            cout << "Fatal input stream error. Exiting.\n";
            keeprunning = false;
            line = "";
            break;
        }

        // trim minimal
        while (!line.empty() && (line[0] == ' ' || line[0] == '\t' || line[0] == '\n')) 
            line.erase(line.begin());
        while (!line.empty() && (line[line.size()-1] == ' ' || line[line.size()-1] == '\t' || line[line.size()-1] == '\n')) 
            line.pop_back();

        if (!line.empty()) return line;
        cout << "Input cannot be empty.\n";
    }
    return "suanloo"; // dummy return to satisfy compiler, should never reach here due to exit on input failure
}

int readIntInRange(const string& prompt, int minV, int maxV) {
    while (true) {
        string s = readNonEmptyLine(prompt);
        if (s.empty()) return -99; // signal error
        
        //only accept 1 or 2 digit numbers (since the menu is 1-11)
        if (s.size()<1||s.size()>2) {
            cout << "Input must be a valid integer between " << minV << " and " << maxV << ".\n";
            continue;
        }
        bool isValid = false;
            if (s.size() == 1) {
                isValid = (s[0] >= '0' && s[0] <= '9');
            } else { // size == 2
                isValid = (s[0] >= '0' && s[0] <= '9') && (s[1] >= '0' && s[1] <= '9');
            }

            if (!isValid) {
                cout << "Invalid input. Please enter digits only.\n";
                continue;
            }
        
        int val= stoi(s);
        if (val < minV || val > maxV) {
            cout << "Input must be a valid integer between " << minV << " and " << maxV << ".\n";
            continue;
        }
        return val;
    }
}

int main() {
    // // 1. Test the Folder Constructor
    // Folder* myFolder = new Folder("Documents", nullptr); 
    // cout << "Success! Folder created with name: " << myFolder->getName() << endl;

    // // 2. Test the File Constructor
    // File myFile("report", "pdf");
    // cout << "Success! File created: " << myFile.getName() << "." << myFile.getExtension() << endl;

    // // 3. Test Memory Cleanup
    // delete myFolder;
    // cout << "Memory cleaned up safely." << endl;

    FileSystem fs;
    bool running = true;

    while (running) {
            cout << "\n===== FILE SYSTEM MENU =====\n";
            cout << "1. Create Folder\n";
            cout << "2. Create File\n";
            cout << "3. Display Current Folder\n";
            cout << "4. Display Full Folder Tree\n";
            cout << "5. Search File\n";
            cout << "6. Enter Folder\n";
            cout << "7. Go Back to Parent Folder\n";
            cout << "8. Delete File\n";
            cout << "9. Delete Folder\n";
            cout << "10. Show Current Path\n";
            cout << "11. Exit\n";
            //I make -99 as invalid input to trigger an error message

            int choice = readIntInRange("Select option (1-11): ", 1, 11);

            switch (choice) {
                case 1: {
                    string folderName = readNonEmptyLine("Folder name: ");
                    if (fs.createFolder(folderName)) {
                        cout << "Folder created.\n";
                    } else {
                        cout << "[Error] Failed to create folder (Does it already exist?).\n";
                    }
                    break;
                }

                case 2: {
                    string fileName = readNonEmptyLine("File name (no extension): ");
                    string ext = readNonEmptyLine("Extension: ");
                    if (fs.createFile(fileName, ext)) {
                        cout << "File created.\n";
                    } else {
                        cout << "[Error] Failed to create file.\n";
                    }
                    break;
                }
                case 3:
                    fs.displayCurrentFolder();
                    break;

                case 4:
                    fs.displayFullTree();
                    break;

                case 5: {
                    string fileName = readNonEmptyLine("Search file name (no extension): ");
                    string ext = readNonEmptyLine("Extension: ");
                    vector<string> results = fs.searchFile(fileName, ext);

                    if (results.empty()) {
                        cout << "No file found.\n";
                    } else {
                        cout << "Found " << (int)results.size() << " match(es):\n";
                        for (int i = 0; i < (int)results.size(); i++) {
                            cout << "  - " << results[i] << "\n";
                        }
                    }
                    break;
                }
                case 6: {
                    string folderName = readNonEmptyLine("Enter folder name: ");
                    if (fs.enterFolder(folderName)) {
                        cout << "Entered folder.\n";
                    } else {
                        cout << "[Error] Folder not found.\n";
                    }
                    break;
                }
                case 7:
                    if (fs.goBackToParentFolder()) {
                        cout << "Moved to parent folder.\n";
                    } else {
                        cout << "[Warning] Already at root folder.\n";
                    }
                    break;

                case 8: {
                    string fileName = readNonEmptyLine("Delete file name (no extension): ");
                    string ext = readNonEmptyLine("Extension: ");
                    if (fs.deleteFile(fileName, ext)) {
                        cout << "File deleted.\n";
                    } else {
                        cout << "[Error] File not found.\n";
                    }
                    break;
                }
                case 9: {
                    string folderName = readNonEmptyLine("Delete folder name: ");
                    if (fs.deleteFolder(folderName)) {
                        cout << "Folder deleted.\n";
                    } else {
                        cout << "[Error] Folder not found.\n";
                    }
                    break;
                }
                case 10:
                    fs.showCurrentPath();
                    break;

                case 11:
                    cout << "Goodbye.\n";
                    running = false; 
                    break;

                default:
                    cout << "Invalid option chosen.\n";
                    break;
            }
        }
    return 0;
}