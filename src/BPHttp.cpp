#include "BPHttp.h"
#include <regex>

BPHttpMessage::BPHttpMessage() {
    this->req_line = "";
}

BPHttpMessage::~BPHttpMessage() {

}

void BPHttpMessage::Parse(std::vector<std::string> lines) {
    //TODO: Decode HTTP request
}

std::string BPHttpMessage::HTTPDateFormatGet() {
    return "";
}