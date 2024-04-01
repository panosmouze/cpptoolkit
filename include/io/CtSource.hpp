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
 * @file CtSource.hpp
 * @brief 
 * @date 08-03-2024
 * 
 */

#ifndef INCLUDE_CTSOURCE_HPP_
#define INCLUDE_CTSOURCE_HPP_

#include "io/CtBlock.hpp"

class CtSource : public CtBlock, CtThread {
public:
    /**
     * @brief This method is used to start a source.
     * 
     * @return void
     */
    EXPORTED_API void startSource();

    /**
     * @brief This method is used to stop a source. It is blocking.
     * 
     * @return void
     */
    EXPORTED_API void stopSource();

    /**
     * @brief This method is used to wait for a source stop reading.
     * 
     * @return void
     */
    EXPORTED_API void joinSource();

    /**
     * @brief This method returns true if the source has data available.
     * 
     * @return bool
     */
    EXPORTED_API bool hasData();

    /**
     * @brief This method returns the first available data from the source.
     * 
     * @return std::vector<CtBlockDataPtr> data vector.
     */
    EXPORTED_API std::vector<CtBlockDataPtr> getData();

    /**
     * @brief This method requests the source to stop. It is not blocking.
     * 
     * @return EXPORTED_API 
     */
    EXPORTED_API void stopSourceRequest();

protected:
    /**
     * @brief This method reserves memory needed by a source. 
     *          Each source has its own resources so this method is virtual.
     * 
     * @return CtBlockDataPtr Returns the generic smart ptr to the resource. 
     */
    EXPORTED_API virtual CtBlockDataPtr newResource() = 0;

    /**
     * @brief Constructor of CtSource.
     * 
     */
    EXPORTED_API CtSource();

    /**
     * @brief Destructor of CtSource.
     * 
     */
    EXPORTED_API ~CtSource();

    /**
     * @brief This virtual method is called to write the CtBlockDataPtr with input data if available.
     * 
     * @param p_data The resource to be written.
     * @return CtUInt32 event code. 
     */
    EXPORTED_API virtual CtUInt32 read(CtBlockDataPtr& p_data) = 0;

private:

    /**
     * @brief This method is the main loop executed by each source.
     * 
     */
    void loop() override;
};

#endif //INCLUDE_CTSOURCE_HPP_