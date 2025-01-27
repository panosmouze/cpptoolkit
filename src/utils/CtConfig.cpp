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
 * @file CtConfig.cpp
 * @brief 
 * @date 10-03-2024
 * 
 */

#include "utils/CtConfig.hpp"

#include "io/CtFileInput.hpp"
#include "io/CtFileOutput.hpp"

#include "exceptions/CtFileExceptions.hpp"
#include "exceptions/CtTypeExceptions.hpp"

#include <string>
#include <map>
#include <fstream>
#include <stdexcept>

CtConfig::CtConfig(const std::string& configFile) : m_configFile(configFile) {
    m_source = nullptr;
    m_sink = nullptr;
}

CtConfig::~CtConfig() {
    if (m_source != nullptr) {
        delete m_source;
    }
    if (m_sink != nullptr) {
        delete m_sink;
    }
}

void CtConfig::read() {
    std::scoped_lock lock(m_mtx_control);
    m_source = new CtFileInput(m_configFile);
    m_source->setDelimiter("\n", 1);

    CtRawData data(512);

    while(m_source->read(&data)) {
        parseLine(std::string((char*)data.get(), data.size()));
        data.reset();
    }

    delete m_source;
    m_source = nullptr;
}

void CtConfig::write() {
    std::scoped_lock lock(m_mtx_control);
    m_sink = new CtFileOutput(m_configFile, CtFileOutput::WriteMode::Truncate);
    m_sink->setDelimiter("\n", 1);
    std::map<std::string, std::string>::iterator iter;

    CtRawData data(512);
    for (iter = m_configValues.begin(); iter != m_configValues.end(); ++iter) {
        std::string line = iter->first + std::string(" = ") + iter->second;
        data.clone((CtUInt8*)line.c_str(), line.size());
        m_sink->write(&data);
        data.reset();
    }

    delete m_sink;
    m_sink = nullptr;
}

void CtConfig::parseLine(const std::string& line) {
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

int32_t CtConfig::parseAsInt(const std::string& key) {
    int32_t parsed_value;
    std::string str_value = getValue(key);
    try {
        parsed_value = stoi(str_value);
    } catch (...) {
        throw CtTypeParseError(std::string("Value of <") + key + std::string("> can not be parsed as int."));
    }
    return parsed_value;
}

uint32_t CtConfig::parseAsUInt(const std::string& key) {
    uint32_t parsed_value;
    std::string str_value = getValue(key);
    try {
        parsed_value = stoul(str_value);
    } catch (...) {
        throw CtTypeParseError(std::string("Value of <") + key + std::string("> can not be parsed as uint."));
    }
    return parsed_value;
}

float CtConfig::parseAsFloat(const std::string& key) {
    float parsed_value;
    std::string str_value = getValue(key);
    try {
        parsed_value = stof(str_value);
    } catch (...) {
        throw CtTypeParseError(std::string("Value of <") + key + std::string("> can not be parsed as float."));
    }
    return parsed_value;
}

double CtConfig::parseAsDouble(const std::string& key) {
    double parsed_value;
    std::string str_value = getValue(key);
    try {
        parsed_value = stod(str_value);
    } catch (...) {
        throw CtTypeParseError(std::string("Value of <") + key + std::string("> can not be parsed as double."));
    }
    return parsed_value;
}

std::string CtConfig::parseAsString(const std::string& key) {
    return getValue(key);
}

std::string CtConfig::getValue(const std::string& key) {
    if (m_configValues.find(key) != m_configValues.end()) {
        return m_configValues[key];
    } else {
        throw CtKeyNotFoundError(std::string("Key <") + key + std::string("> not found."));
    }
}

void CtConfig::writeInt(const std::string& p_key, const int32_t& p_value) {
    writeString(p_key, std::to_string(p_value));
}

void CtConfig::writeUInt(const std::string& p_key, const uint32_t& p_value) {
    writeString(p_key, std::to_string(p_value));
}

void CtConfig::writeFloat(const std::string& p_key, const float& p_value) {
    writeString(p_key, std::to_string(p_value));
}

void CtConfig::writeDouble(const std::string& p_key, const double& p_value) {
    writeString(p_key, std::to_string(p_value));
}

void CtConfig::writeString(const std::string& p_key, const std::string& p_value) {
    m_configValues[p_key] = p_value;
}
