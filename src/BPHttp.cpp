#include "BPHttp.h"
#include <regex>
#include <iostream>

BPHttpMessage::BPHttpMessage() {
    this->msg_type = "";
    this->entity_head = "";
    this->body = "";
    this->header_map = {};
}   

BPHttpMessage::~BPHttpMessage() {

}

void BPHttpMessage::Parse(std::vector<std::string> lines) {
    std::smatch match;
    std::string pattern_req = "(POST|GET|PUT|HEAD|DELETE|CONNECT|OPTIONS|TRACE)\\s+([a-zA-Z\\/.-]+)\\s+([a-zA-Z]+)\\/([0-9.]+)$";
    std::string pattern_resp = "HTTP\\/([0-9.]+)\\s+([0-9]+)\\s+(.*)";
    std::string pattern_header = "^([a-zA-Z-]+):\\s+(.*)\n*";
    
    std::regex regex_req(pattern_req);
    std::regex regex_resp(pattern_resp);
    std::regex regex_header(pattern_header);
    
    bool body_trigger = false;

    for (std::vector<std::string>::iterator it = lines.begin(); it != lines.end(); it++) {
        std::cout << *it << std::endl;
        if (std::regex_match(*it, match, regex_req) && !body_trigger) {
            this->msg_type = "request";
            this->entity_head = *it;
        } else if (std::regex_match(*it, match, regex_resp ) && !body_trigger) {
            this->msg_type = "response";
            this->entity_head = *it;
        } else if (std::regex_match(*it, match, regex_header) && !body_trigger) {
            this->header_map[match[1]] = match[2];
        } else {
            if (*it != "") {
                this->body += *it+"\n";
            }            
        }
    }
    


}

std::string BPHttpMessage::HTTPDateFormatGet() {
    return "";
}