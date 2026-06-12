/*todo
[]check if thhe filestystem can be connected to the main.cpp
[]check if the function of file and folder can call and used inside filesystem.cpp, or need using virtual function
[]check if the input and output of the function in file and folder can be used in the main.cpp
[]check if can understand the code and the logic of the code, if not understand, need to add more comment to explain the code
*/
#include "FileSystem.h"

FileSystem::FileSystem() {
    root = new Folder("Root", nullptr);
    currentFolder = root;
    loadFileSystem("filesystem.txt"); // now we will load the file system from the file in constructor
}

FileSystem::~FileSystem() {
    delete root;  // recursiveDelete() handles children
}

vector<string> FileSystem::searchFile(const string& name, const string& extension) {
    vector<string> results;
    string fullName = name + "." + extension;
    root->searchFile(fullName, "", results);
    return results;
}

// Returns true if folder created successfully, false if a folder with the same name already exists
bool FileSystem::createFolder(const string& folderName) {
    if (currentFolder->findSubfolder(folderName) != nullptr) {
        return false; // Folder already exists
    }
    Folder* newFolder = new Folder(folderName, currentFolder);
    currentFolder->addSubfolder(newFolder);
    return true;
}

// Returns true if file created successfully, false if a file with the same name already exists
bool FileSystem::createFile(const string& fileName, const string& extension) {
    string fullName = fileName + "." + extension;
    if (currentFolder->fileExists(fullName)) {
        return false; // File already exists
    }
    currentFolder->addFile(File(fileName, extension));
    return true;
}

// Returns true if file deleted successfully, false if file not found
bool FileSystem::deleteFile(const string& fileName, const string& extension) {
    string fullName = fileName + "." + extension;
    return currentFolder->removeFile(fullName);
}

// Returns true if entered folder successfully, false if folder not found
bool FileSystem::deleteFolder(const string& folderName) {
    return currentFolder->removeSubfolderByName(folderName); // folder have no extension name. So no extra string operation
}

bool FileSystem::enterFolder(const string& folderName) {
    Folder* nextFolder = currentFolder->findSubfolder(folderName);
    if (nextFolder != nullptr) {
        currentFolder = nextFolder;
        return true;
    }
    return false;
}

bool FileSystem::goBackToParentFolder() {
    if (currentFolder->getParent() != nullptr) {
        currentFolder = currentFolder->getParent();
        return true;
    }
    return false; // Already at root
}

void FileSystem::displayCurrentFolder() {
    cout << "Contents of " << currentFolder->getName() << ":\n";
    for (const File& f : currentFolder->getFiles()) {
        cout << "  - " << f.getFullName() << "\n";
    }
    for (Folder* const sub : currentFolder->getSubfolders()) {
        cout << "  [Folder] " << sub->getName() << "\n";
    }
}

void FileSystem::displayFullTree() {
    cout << "File System Tree:\n";
    root->displayTree();
}

void FileSystem::showCurrentPath() {
    cout << "Current path: " << currentFolder->getPath() << "\n";
}

void FileSystem::loadFileSystem(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "[DEBUG] ERROR: Could not open " << filename << endl;//edbug
        return; // File doesn't exist, just skip
    }
    cout << "[DEBUG] Successfully opened " << filename << endl;//debug
    int lineCount = 0;//debug

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        // Parse FOLDER lines
        if (line.substr(0, 7) == "FOLDER ") {
            string path = line.substr(7); // Remove "FOLDER " prefix
            Folder* current = root;

            // Navigate/create folders along the path
            int start = 0;
            while (start < path.length()) {
                int slash = path.find('/', start);
                if (slash == -1) slash = path.length();
                
                string folderName = path.substr(start, slash - start);
                
                // Skip "Root" as it's already created
                if (folderName == "Root") {
                    start = slash + 1;
                    continue;
                }

                // Find or create subfolder
                Folder* existing = current->findSubfolder(folderName);
                if (existing == nullptr) {
                    Folder* newFolder = new Folder(folderName, current);
                    current->addSubfolder(newFolder);
                    current = newFolder;
                } else {
                    current = existing;
                }
                
                start = slash + 1;
            }
        }
        // Parse FILE lines
        else if (line.substr(0, 5) == "FILE ") {
            string path = line.substr(5); // Remove "FILE " prefix

            // Find last slash to separate folder path from filename
            int lastSlash = path.rfind('/');
            if (lastSlash == -1) continue;

            string folderPath = path.substr(0, lastSlash);
            string fileFullName = path.substr(lastSlash + 1);

            // Navigate to the target folder
            Folder* current = root;
            int start = 0;
            while (start < folderPath.length()) {
                int slash = folderPath.find('/', start);
                if (slash == -1) slash = folderPath.length();
                
                string folderName = folderPath.substr(start, slash - start);

                if (folderName != "Root") {
                    Folder* existing = current->findSubfolder(folderName);
                    if (existing != nullptr) {
                        current = existing;
                    }
                }
                
                start = slash + 1;
            }

            // Extract filename and extension
            int dotPos = fileFullName.rfind('.');
            string fileName, extension;
            if (dotPos != -1) {
                fileName = fileFullName.substr(0, dotPos);
                extension = fileFullName.substr(dotPos + 1);
            } else {
                fileName = fileFullName;
                extension = "";
            }

            // Add file to current folder if it doesn't exist
            if (!current->fileExists(fileFullName)) {
                current->addFile(File(fileName, extension));
            }
        }
    }
    file.close();
    currentFolder = root; // Reset to root after loading
}

