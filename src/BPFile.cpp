#include "BPFile.h"

bool BPFile::FileExists(const std::string& path) {
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0);
}

bool BPFile::FileReadLines(std::string filePath, std::vector<std::string>* ret) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        return false;
    } else {
        std::string line ="";
        while (std::getline(file, line) && !file.eof()) {
            ret->push_back(line);
            line = "";
        }
    }
    return true;
}

bool BPFile::FileReadString(std::string filePath, std::string* file) {
    std::ifstream fileobj(filePath);
    std::stringstream buffer;  
    if (fileobj.is_open()) {
        buffer << fileobj.rdbuf();
        *file = buffer.str();
    } else {
        return false;
    }
    return true;
}