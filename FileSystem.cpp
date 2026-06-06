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
}

FileSystem::~FileSystem() {
    delete root;  // recursiveDelete() handles children
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

vector<string> FileSystem::searchFile(const string& name, const string& extension) {
    vector<string> results;
    string fullName = name + "." + extension;
    root->searchFile(fullName, "", results);
    return results;
}