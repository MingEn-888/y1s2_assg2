#include <iostream>
#include "File.h"
#include "Folder.h"

using namespace std;

int main() {
    // 1. Test the Folder Constructor
    Folder* myFolder = new Folder("Documents", nullptr); 
    cout << "Success! Folder created with name: " << myFolder->getName() << endl;

    // 2. Test the File Constructor
    File myFile("report", "pdf");
    cout << "Success! File created: " << myFile.getName() << "." << myFile.getExtension() << endl;

    // 3. Test Memory Cleanup
    delete myFolder;
    cout << "Memory cleaned up safely." << endl;

    return 0;
}