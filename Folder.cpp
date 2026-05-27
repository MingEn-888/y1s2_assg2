#include "Folder.h"

// Constructor
Folder::Folder(const string& n, Folder* p) {
    name = n;
    parent = p;
    // **The vectors for files and subfolders will initialize as empty automatically.
}

string Folder::getName() const {
    return name;
}