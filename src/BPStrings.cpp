#include "BPStrings.h"

std::vector<std::string> BPStrings::SplitString(const std::string inputString, char delimiter) {
    std::vector<std::string> substrings;
    size_t start = 0;
    size_t end = inputString.find(delimiter);
    while (end != std::string::npos) {
        substrings.push_back(inputString.substr(start, end - start));
        start = end + 1;
        end = inputString.find(delimiter, start);
    }
    substrings.push_back(inputString.substr(start));
    return substrings;
}

std::string BPStrings::EscapeStringCharacters(std::string msg) {
    std::string ret = "";
    std::unordered_map<char, bool> sequences = {{'\'', true}, {'"', true}, {'/', true}, {'<', true}, {'>', true}, {'{', true}, {'}', true}, {'[', true}, {']', true}, {'&', true}};
    for (long unsigned int i=0; i < msg.size(); i++) {
        if (sequences[msg[i]]) {
            ret+= ("\\"+msg[i]);
        } else {
            ret+= msg[i];
        }
    }
    return ret;
}