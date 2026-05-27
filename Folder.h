#ifndef FOLDER_H
#define FOLDER_H

#include <string>
#include <vector>
#include "File.h"
using namespace std;

class Folder {
private:
    string name;
    Folder* parent;
    vector<File> files;
    vector<Folder*> subfolders;
public:
    Folder(const string& name, Folder* parent = nullptr);
    void addFile(const File& file);
    const vector<File>& getFiles() const;
    void addSubfolder(Folder* subfolder);
    const vector<Folder*>& getSubfolders() const;

    string getName() const;
};

#endif