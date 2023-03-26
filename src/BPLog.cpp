#include "BPLog.h"

void BPMainLog::WriteLog(std::string line, std::string path) {
    std::string log = "echo $(date):"+line+" >> "+ path;
    system(log.c_str());
}

void BPErrorLog::WriteLog(std::string line, std::string path) {
    std::string log = "echo $(date):" +line+ " >> "+ path;
    system(log.c_str());
}