/*
 * CtConfigParser.cpp
 *
 *  Created on: Nov 13, 2023
 *      Author: Mouzenidis Panagiotis
 */

#include "io/CtConfigParser.hpp"
#include "exceptions/CtFileError.hpp"
#include "exceptions/CtTypeParseError.hpp"
#include "exceptions/CtFileParseError.hpp"
#include "exceptions/CtKeyNotFoundError.hpp"
#include <string>
#include <map>
#include <fstream>
#include <stdexcept>

CtConfigParser::CtConfigParser(const std::string& configFile) : m_configFile(configFile) {
    try {
        std::ifstream fileStream;
        fileStream.open(m_configFile);

        if (fileStream.is_open()) {
            std::string line;
            while (std::getline(fileStream, line)) {
                parseLine(line);
            }
            
            fileStream.close();
        }
    } catch (const CtFileParseError& e) {
        throw e;
    } catch (...) {
        throw CtFileError("");
    }
}

CtConfigParser::~CtConfigParser() {

}

void CtConfigParser::parseLine(const std::string& line) {
    size_t separatorPos = line.find('=');
    size_t commentPos = line.find('#');
    size_t eol = line.size();
    bool hasComment = commentPos != std::string::npos;
    bool hasSeparator = separatorPos != std::string::npos;

    if (hasSeparator && hasComment) {
        if (separatorPos > commentPos) {
            throw CtFileParseError("");
        } else {
            eol = commentPos;
        }
    } else if (!hasSeparator && !hasComment) {
        throw CtFileParseError("");
    } else if (!hasSeparator && hasComment) {
        return;
    }

    std::string key = line.substr(0, separatorPos);
    std::string value = line.substr(separatorPos + 1, eol - (separatorPos + 1));

    key.erase(0, key.find_first_not_of(" \t\r\n"));
    key.erase(key.find_last_not_of(" \t\r\n") + 1);
    value.erase(0, value.find_first_not_of(" \t\r\n"));
    value.erase(value.find_last_not_of(" \t\r\n") + 1);

    m_configValues[key] = value;
}

int32_t CtConfigParser::parseAsInt(const std::string& key) {
    int32_t parsed_value;
    std::string str_value = getValue(key);
    try {
        parsed_value = stoi(str_value);
    } catch (...) {
        throw CtTypeParseError("");
    }
    return parsed_value;
}

uint32_t CtConfigParser::parseAsUInt(const std::string& key) {
    uint32_t parsed_value;
    std::string str_value = getValue(key);
    try {
        parsed_value = stoul(str_value);
    } catch (...) {
        throw CtTypeParseError("");
    }
    return parsed_value;
}

float CtConfigParser::parseAsFloat(const std::string& key) {
    float parsed_value;
    std::string str_value = getValue(key);
    try {
        parsed_value = stof(str_value);
    } catch (...) {
        throw CtTypeParseError("");
    }
    return parsed_value;
}

double CtConfigParser::parseAsDouble(const std::string& key) {
    double parsed_value;
    std::string str_value = getValue(key);
    try {
        parsed_value = stod(str_value);
    } catch (...) {
        throw CtTypeParseError("");
    }
    return parsed_value;
}

std::string CtConfigParser::parseAsString(const std::string& key) {
    return getValue(key);
}

std::string CtConfigParser::getValue(const std::string& key) {
    if (m_configValues.find(key) != m_configValues.end()) {
        return m_configValues[key];
    } else {
        throw CtKeyNotFoundError("");
    }
}