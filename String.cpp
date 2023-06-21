//
// Created by kurum on 西暦2023年6月20日.
//

#include "String.h"

std::vector<std::string> String::split(std::string input,  std::string delimiters) {
    std::vector<std::string> result;
    size_t pos = 0;
    size_t prev = 0;

    while ((pos = input.find_first_of(delimiters, prev)) != std::string::npos) {
        if (pos > prev) {
            result.push_back(input.substr(prev, pos - prev));
        }
        prev = pos + 1;
    }

    if (prev < input.length()) {
        result.push_back(input.substr(prev));
    }
    return result;
}

