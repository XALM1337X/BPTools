#include "BPHttp.h"
#include "BPStrings.h"
#include "BPExec.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <regex>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>

BPHttpMessage::BPHttpMessage() {
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

bool BPHttpMessage::SendRequest(std::string host_ip, int port, std::string msg, std::string* out_data, std::string* err_out) {
    
    sockaddr_in serverAddress;
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);    
    if (clientSocket < 0) {
        *err_out = "Failed to create client socket";
        return false;
    }
    struct hostent* host = gethostbyname(host_ip.c_str());    
    if (host != NULL) {
        struct in_addr* addr = (struct in_addr*)host->h_addr;    
        serverAddress.sin_addr.s_addr = addr->s_addr;
    } else {
        serverAddress.sin_addr.s_addr = inet_addr(host_ip.c_str());
    }
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    
    if (connect(clientSocket, (struct sockaddr*) &serverAddress, sizeof(serverAddress)) < 0) {
        *err_out = "Error connecting to server";
        return false;
    }
    // set the socket to blocking mode
    int flags = fcntl(clientSocket, F_GETFL, 0);
    fcntl(clientSocket, F_SETFL, flags & ~O_NONBLOCK);    
    send(clientSocket, msg.c_str(), strlen(msg.c_str()), 0);
    if (shutdown(clientSocket, SHUT_WR) == -1) {
    // error handling code for shutdown function call
        *err_out = "Error shutting down socket";
        return false;
    }
    fd_set read_fds;
    FD_ZERO(&read_fds);
    FD_SET(clientSocket, &read_fds);

    struct timeval timeout;
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    int numReady = select(clientSocket + 1, &read_fds, NULL, NULL, &timeout);
    if (numReady != -1 && numReady != 0) {
        char* buffer = (char*)malloc(1024*1024*5);
        ssize_t valread = 0;
        size_t buffer_size = 1024*1024*5;
        while ((valread = recv(clientSocket, buffer, buffer_size, 0)) > 0) {
            buffer_size += valread;
            buffer = (char*)realloc(buffer, buffer_size);
            if (buffer == NULL) {
                *err_out = "Failed to allocate memory for response buffer";
        return false;
    }
            *out_data += std::string(buffer);
            std::cout << buffer << std::endl;
        }
    }

    close(clientSocket);

    //return true;
    return false;
}

std::string BPHttpMessage::BuildMessageString() {
    std::string ret_string = "";
    ret_string+=this->entity_head+"\r\n";
    for (const auto& pair : this->header_map) {
        ret_string+=pair.first+": "+pair.second+"\r\n";
    }
    ret_string+="\r\n";
    ret_string+=this->body;    
    return ret_string;
}

void BPHttpMessage::EntityHeadSet(std::string element1, std::string element2, std::string element3) {    
    this->entity_head = element1 +" "+ element2 +" "+element3;
}
void BPHttpMessage::HeaderSet(std::string key, std::string val) {
    this->header_map[key] = val;
}
void BPHttpMessage::BodySet(std::string str_body) {
    this->body = str_body;
}

std::string BPHttpMessage::HTTPDateFormatGet() {
    return "";
}

void BPHttpMessage::ClearBody() {
    this->body = "";
}