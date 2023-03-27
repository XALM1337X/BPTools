#ifndef BPHTTP_H
#define BPHTTP_H
#include <unordered_map>
#include <string>
#include <vector>
class BPHttpMessage {
    public:
        BPHttpMessage();
        ~BPHttpMessage();
        void Parse(std::vector<std::string>);
        //TODO: Add method to make this system call for the date:  date -u +"%a, %d %b %Y %H:%M:%S GMT"
        std::string HTTPDateFormatGet();
    
    public:
        std::string msg_type;
        std::string entity_head;
        std::unordered_map<std::string, std::string> header_map;  
        std::string body;      
};
#endif