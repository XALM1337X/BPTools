#ifndef BPLOG_H
#define BPLOG_H
#include <string>

class BPMainLog {
    public:
        static void WriteLog(std::string,std::string);
};


class BPErrorLog {
    public:
        static void WriteLog(std::string,std::string);
};


#endif