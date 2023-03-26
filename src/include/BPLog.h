#ifndef BPLOG_H_
#define BPLOG_H_
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