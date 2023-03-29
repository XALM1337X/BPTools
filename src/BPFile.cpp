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
        while (std::getline(file, line)) {
            ret->push_back(line);
            line = "";
        }
    }
    return true;
}

bool BPFile::FileReadString(std::string filePath, std::string* str) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        return false;
    } else {
        std::string line ="";
        while (std::getline(file, line)) {
            if (file.eof()) {
                *str+=line;
            } else {
                *str+=line+"\r\n";
            }
            line = "";
        }
    }
    return true;
}