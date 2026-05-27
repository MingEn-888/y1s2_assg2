#ifndef FILE_H
#define FILE_H

#include <string>
using namespace std;

class File {
private:
    string name;
    string extension;
public:
    File(const string& name, const string& extension);
    string getName() const;
    string getExtension() const;

};

#endif