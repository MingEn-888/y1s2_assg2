#include "Folder.h"
#include <iostream>
#include <algorithm>
using namespace std;

Folder::Folder(const string& name, Folder* parent)
    : name(name), parent(parent) {}

Folder::~Folder() {
    recursiveDelete();
}

string Folder::getName() const {
    return name;
}

Folder* Folder::getParent() const {
    return parent;
}

vector<File>& Folder::getFiles() {
    return files;
}

vector<Folder*>& Folder::getSubfolders() {
    return subfolders;
}


void Folder::addFile(const File& file) {
    files.push_back(file);
}

bool Folder::removeFile(const string& fullName) {
    for (auto it = files.begin(); it != files.end(); ++it) {
        if (it->getFullName() == fullName) {
            files.erase(it);
            return true;
        }
    }
    return false;
}

bool Folder::fileExists(const string& fullName) const {
    for (const auto& f : files) {
        if (f.getFullName() == fullName) {
            return true;
        }
    }
    return false;
}


void Folder::addSubfolder(Folder* folder) {
    subfolders.push_back(folder);
}

bool Folder::removeSubfolderByName(const string& folderName) {
    for (auto it = subfolders.begin(); it != subfolders.end(); ++it) {
        if ((*it)->getName() == folderName) {
            delete *it;
            subfolders.erase(it);
            return true;
        }
    }
    return false;
}

Folder* Folder::findSubfolder(const string& folderName) const {
    for (Folder* f : subfolders) {
        if (f->getName() == folderName) {
            return f;
        }
    }
    return nullptr;
}

string Folder::getPath() const {
    vector<string> parts;
    const Folder* current = this;
    while (current != nullptr) {
        parts.push_back(current->name);
        current = current->parent;
    }
    string path = "";
    for (int i = (int)parts.size() - 1; i >= 0; i--) {
        path += parts[i];
        if (i != 0) path += "/";
    }
    return path;
}

void Folder::displayTree(const string& prefix) const {
    cout << name << endl;

    int totalFiles = (int)files.size();
    int totalFolders = (int)subfolders.size();
    int total = totalFiles + totalFolders;
    int index = 0;

    for (int i = 0; i < totalFiles; i++, index++) {
        bool isLast = (index == total - 1);
        string connector = isLast ? "`-- " : "|-- ";
        cout << prefix << connector << files[i].getFullName() << endl;
    }

    for (int i = 0; i < totalFolders; i++, index++) {
        bool isLast = (index == total - 1);
        string connector = isLast ? "`-- " : "|-- ";

        cout << prefix << connector;

        string newPrefix = prefix + (isLast ? "    " : "|   ");

        subfolders[i]->displayTree(newPrefix);
    }
}

void Folder::searchFile(const string& fullName, const string& currentPath,
                        vector<string>& results) const {
    // Base case: search files in the current folder
    for (const auto& f : files) {
        if (f.getFullName() == fullName) {
            results.push_back(currentPath + "/" + fullName);
        }
    }

    // Recursive case: search each subfolder
    for (Folder* sub : subfolders) {
        sub->searchFile(fullName, currentPath + "/" + sub->getName(), results);
    }
}


void Folder::recursiveDelete() {
    for (Folder* sub : subfolders) {
        sub->recursiveDelete(); // free sub's children
        sub->subfolders.clear(); // prevent ~Folder from re-running recursiveDelete
        delete sub;
    }
    subfolders.clear();
}