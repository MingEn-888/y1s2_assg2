#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Folder.h"
#include "File.h"
using namespace std;

class FileSystem {
private:
    Folder* root;
    Folder* currentFolder;
    
public:
    FileSystem();
    ~FileSystem();
    void loadFileSystem(const string& filename);
    bool createFolder(const std::string& name);
    bool createFile(const std::string& name, const std::string& extension);
    void displayCurrentFolder();
    void displayFullTree();
    std::vector<std::string> searchFile(const std::string& name, const std::string& extension);
    bool enterFolder(const std::string& name);
    bool goBackToParentFolder();
    bool deleteFile(const std::string& name, const std::string& extension);
    bool deleteFolder(const std::string& name);
    void showCurrentPath();
};

#endif