#ifndef BPEXEC_H
#define BPEXEC_H
#include <fstream>
#include <iostream>
#include <string>


class BPExecResult {
    public:
        int exit_code;
        std::string result;
        std::string err_str;
};

class BPExec {
    public:
        static BPExecResult Exec(std::string,bool);
               
};

#endif