#ifndef BPFILE_H
#define BPFILE_H
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/stat.h>


class BPFile {
    public:
        static bool FileExists(const std::string&) ;          
        static bool FileReadLines(std::string, std::vector<std::string>*);        
        static bool FileReadString(std::string, std::string*);
        
};

#endif