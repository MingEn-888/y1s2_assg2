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
        vector<Folder*> subfolders;
        vector<File> files;
    public:
        // Constructor / Destructor
    Folder(const string& name, Folder* parent = nullptr);
    ~Folder(); // calls recursive cleanup internally
 
    // Getters
    string getName() const;
    Folder* getParent() const;
    vector<File>& getFiles();
    vector<Folder*>& getSubfolders();
 
    // File management
    void addFile(const File& file);
    bool removeFile(const string& fullName); // e.g. "notes.pdf"
    bool fileExists(const string& fullName) const;
 
    // Folder management
    void addSubfolder(Folder* folder);
    bool removeSubfolderByName(const string& folderName);
    Folder* findSubfolder(const string& folderName) const;


void displayTree(const string& prefix = "") const;

void searchFile(const string& fullName, const string& currentPath, vector<string>& results) const;

void recursiveDelete();

string getPath() const;

};

#endif