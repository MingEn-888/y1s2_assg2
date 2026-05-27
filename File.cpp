#include "File.h"

// Constructor
File::File(const string& n, const string& ext) {
    name = n;
    extension = ext;
}

string File::getName() const {
    return name;
}

string File::getExtension() const {
    return extension;
}