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

CtConfig::CtConfig(const CtString& configFile) : m_configFile(configFile) {
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
        parseLine(CtString((CtChar*)data.get(), data.size()));
        data.reset();
    }

    delete m_source;
    m_source = nullptr;
}

void CtConfig::write() {
    std::scoped_lock lock(m_mtx_control);
    m_sink = new CtFileOutput(m_configFile, CtFileOutput::WriteMode::Truncate);
    m_sink->setDelimiter("\n", 1);
    CtMap<CtString, CtString>::iterator iter;

    CtRawData data(512);
    for (iter = m_configValues.begin(); iter != m_configValues.end(); ++iter) {
        CtString line = iter->first + CtString(" = ") + iter->second;
        data.clone((CtUInt8*)line.c_str(), line.size());
        m_sink->write(&data);
        data.reset();
    }

    delete m_sink;
    m_sink = nullptr;
}

void CtConfig::parseLine(const CtString& line) {
    size_t separatorPos = line.find('=');
    size_t commentPos = line.find('#');
    size_t eol = line.size();
    CtBool hasComment = commentPos != CtString::npos;
    CtBool hasSeparator = separatorPos != CtString::npos;

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

    CtString key = line.substr(0, separatorPos);
    CtString value = line.substr(separatorPos + 1, eol - (separatorPos + 1));

    key.erase(0, key.find_first_not_of(" \t\r\n"));
    key.erase(key.find_last_not_of(" \t\r\n") + 1);
    value.erase(0, value.find_first_not_of(" \t\r\n"));
    value.erase(value.find_last_not_of(" \t\r\n") + 1);

    m_configValues[key] = value;
}

CtInt32 CtConfig::parseAsInt(const CtString& key) {
    CtString str_value = getValue(key);
    return CtStringHelpers::StrToInt(str_value);
}

CtUInt32 CtConfig::parseAsUInt(const CtString& key) {
    CtString str_value = getValue(key);
    return CtStringHelpers::StrToUInt(str_value);
}

CtFloat CtConfig::parseAsFloat(const CtString& key) {
    CtString str_value = getValue(key);
    return CtStringHelpers::StrToFloat(str_value);
}

CtDouble CtConfig::parseAsDouble(const CtString& key) {
    CtString str_value = getValue(key);
    return CtStringHelpers::StrToDouble(str_value);
}

CtString CtConfig::parseAsString(const CtString& key) {
    return getValue(key);
}

CtString CtConfig::getValue(const CtString& key) {
    if (m_configValues.find(key) != m_configValues.end()) {
        return m_configValues[key];
    } else {
        throw CtKeyNotFoundError(CtString("Key <") + key + CtString("> not found."));
    }
}

void CtConfig::writeInt(const CtString& p_key, const CtInt32& p_value) {
    writeString(p_key, std::to_string(p_value));
}

void CtConfig::writeUInt(const CtString& p_key, const CtUInt32& p_value) {
    writeString(p_key, std::to_string(p_value));
}

void CtConfig::writeFloat(const CtString& p_key, const CtFloat& p_value) {
    writeString(p_key, std::to_string(p_value));
}

void CtConfig::writeDouble(const CtString& p_key, const CtDouble& p_value) {
    writeString(p_key, std::to_string(p_value));
}

void CtConfig::writeString(const CtString& p_key, const CtString& p_value) {
    m_configValues[p_key] = p_value;
}
