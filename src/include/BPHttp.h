#ifndef BPHTTP_H
#define BPHTTP_H
#include <unordered_map>
#include <string>
#include <vector>
#include <regex>

class BPHttpMessage {
    public:
        BPHttpMessage();
        ~BPHttpMessage();
        bool Parse(std::vector<std::string>);
        std::string HTTPDateFormatGet();
        std::string ParseRequestResource(std::string);
        static bool SendRequest(std::string, int, std::string, std::string*, std::string*);
        std::string BuildMessageString();
        void EntityHeadSet(std::string, std::string, std::string);
        void HeaderSet(std::string, std::string);
        void BodySet(std::string);
        static void GenerateDate(std::string*, std::string*);        
        void ClearBody();    
    public:
        std::string entity_head;
        std::unordered_map<std::string, std::string> header_map;  
        std::string body;
        std::string pattern_req;
        std::string pattern_resp;
        std::string pattern_header;
        std::regex* regex_req;
        std::regex* regex_resp;
        std::regex* regex_header;     

};

#endif