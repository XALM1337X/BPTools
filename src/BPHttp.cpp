#include "BPHttp.h"
#include "BPStrings.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <regex>
#include <iostream>
#include <unistd.h>

BPHttpMessage::BPHttpMessage() {
    this->msg_type = "";
    this->entity_head = "";
    this->body = "";
    this->header_map = {};
    this->pattern_req = "([A-Z]+)\\s+([a-zA-Z0-9\\-._~:\\/?#\\[\\]@!$&'()*+,;=]+)\\s+([a-zA-Z]+)\\/([0-9.]+)\r*$";
    this->pattern_resp = "HTTP\\/([0-9.]+)\\s+([0-9]+)\\s+(.*)\r*$";
    this->pattern_header = "^([a-zA-Z-]+):\\s+(.*)\r*$";
}   

BPHttpMessage::~BPHttpMessage() {

}

bool BPHttpMessage::Parse(std::vector<std::string> lines) {
    std::smatch match;    
    std::regex regex_req(this->pattern_req);
    std::regex regex_resp(this->pattern_resp);
    std::regex regex_header(this->pattern_header);
    bool ent_head_flag = false;
    bool head_flag = false;

    for (std::vector<std::string>::iterator it = lines.begin(); it != lines.end(); it++) {
        if (std::regex_match(*it, match, regex_req)) {
            this->msg_type = "request";
            this->entity_head = *it;
            ent_head_flag = true;
        } else if (std::regex_match(*it, match, regex_resp )) {
            this->msg_type = "response";
            this->entity_head = *it;
        } else if (std::regex_match(*it, match, regex_header)) {
            this->header_map[match[1]] = match[2];
            head_flag = true;
        } else {
            if (*it != "") {
                this->body += *it+"\n";
            }            
        }
    }
    if (ent_head_flag && head_flag) {
        return true;
    }
    this->msg_type = "";
    this->entity_head = "";
    this->body = "";
    this->header_map.clear();
    return false;
}

std::string BPHttpMessage::ParseRequestResource(std::string ent_head) {
    std::vector<std::string> splt = BPStrings::SplitString(ent_head, ' ');
    if (splt.size() > 0) {
        return splt[1];
    }
    return "";
}

std::string BPHttpMessage::HTTPDateFormatGet() {
    return "";
}