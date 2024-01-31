/*
MIT License

Copyright (c) 2024 Mouzenidis Panagiotis

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/**
 * @file CtConfigIO.cpp
 * @brief 
 * @date 18-01-2024
 * 
 */

#include "io/CtConfigIO.hpp"
#include "exceptions/CtFileExceptions.hpp"
#include "exceptions/CtGenericExeptions.hpp"
#include <string>
#include <map>
#include <fstream>
#include <stdexcept>

CtConfigIO::CtConfigIO(const std::string& configFile) : m_configFile(configFile) {
}

CtConfigIO::~CtConfigIO() {
}

void CtConfigIO::read() {
    try {
        m_fileStream.open(m_configFile, std::ofstream::in);

        if (m_fileStream.is_open()) {
            std::string line;
            while (std::getline(m_fileStream, line)) {
                parseLine(line);
            }
            
            m_fileStream.close();
        }
    } catch (const CtFileParseError& e) {
        throw e;
    } catch (...) {
        throw CtFileReadError("File not found.");
    }
}

void CtConfigIO::write() {
    try {
        m_fileStream.open(m_configFile, std::ofstream::out | std::ofstream::trunc);

        if (m_fileStream.is_open()) {
            std::map<std::string, std::string>::iterator iter;
            std::string line;
            for (iter = m_configValues.begin(); iter != m_configValues.end(); iter++) {
                line = iter->first + std::string(" = ") + iter->second + std::string("\n");
                m_fileStream << line;
            }
            
            m_fileStream.close();
        }
    } catch (...) {
        throw CtFileWriteError("File not found.");
    }
}

void CtConfigIO::parseLine(const std::string& line) {
    size_t separatorPos = line.find('=');
    size_t commentPos = line.find('#');
    size_t eol = line.size();
    bool hasComment = commentPos != std::string::npos;
    bool hasSeparator = separatorPos != std::string::npos;

    if (hasSeparator && hasComment) {
        if (separatorPos > commentPos) {
            throw CtFileParseError("Invalid comment.");
        } else {
            eol = commentPos;
        }
    } else if (!hasSeparator && !hasComment) {
        throw CtFileParseError("Invalid line entry.");
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

int32_t CtConfigIO::parseAsInt(const std::string& key) {
    int32_t parsed_value;
    std::string str_value = getValue(key);
    try {
        parsed_value = stoi(str_value);
    } catch (...) {
        throw CtTypeParseError(std::string("Value of <") + key + std::string("> can not be parsed as int."));
    }
    return parsed_value;
}

uint32_t CtConfigIO::parseAsUInt(const std::string& key) {
    uint32_t parsed_value;
    std::string str_value = getValue(key);
    try {
        parsed_value = stoul(str_value);
    } catch (...) {
        throw CtTypeParseError(std::string("Value of <") + key + std::string("> can not be parsed as uint."));
    }
    return parsed_value;
}

float CtConfigIO::parseAsFloat(const std::string& key) {
    float parsed_value;
    std::string str_value = getValue(key);
    try {
        parsed_value = stof(str_value);
    } catch (...) {
        throw CtTypeParseError(std::string("Value of <") + key + std::string("> can not be parsed as float."));
    }
    return parsed_value;
}

double CtConfigIO::parseAsDouble(const std::string& key) {
    double parsed_value;
    std::string str_value = getValue(key);
    try {
        parsed_value = stod(str_value);
    } catch (...) {
        throw CtTypeParseError(std::string("Value of <") + key + std::string("> can not be parsed as double."));
    }
    return parsed_value;
}

std::string CtConfigIO::parseAsString(const std::string& key) {
    return getValue(key);
}

std::string CtConfigIO::getValue(const std::string& key) {
    if (m_configValues.find(key) != m_configValues.end()) {
        return m_configValues[key];
    } else {
        throw CtKeyNotFoundError(std::string("Key <") + key + std::string("> not found."));
    }
}

void CtConfigIO::writeInt(const std::string& p_key, const int32_t& p_value) {
    writeString(p_key, std::to_string(p_value));
}

void CtConfigIO::writeUInt(const std::string& p_key, const uint32_t& p_value) {
    writeString(p_key, std::to_string(p_value));
}

void CtConfigIO::writeFloat(const std::string& p_key, const float& p_value) {
    writeString(p_key, std::to_string(p_value));
}

void CtConfigIO::writeDouble(const std::string& p_key, const double& p_value) {
    writeString(p_key, std::to_string(p_value));
}

void CtConfigIO::writeString(const std::string& p_key, const std::string& p_value) {
    m_configValues[p_key] = p_value;
}
