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
 * @file CtSink.hpp
 * @brief 
 * @date 09-03-2024
 * 
 */

#ifndef INCLUDE_CTSINK_HPP_
#define INCLUDE_CTSINK_HPP_

#include "io/CtBlock.hpp"

class CtSink : public CtBlock, CtThread {
public:
    /**
     * @brief This method is used to start a sink.
     * 
     * @return void
     */
    EXPORTED_API void startSink();

    /**
     * @brief This method is used to stop a sink. It is blocking.
     * 
     * @return void
     */
    EXPORTED_API void stopSink();

    /**
     * @brief Thi smethod is used to wait a sink to stop.
     * 
     * @return void 
     */
    EXPORTED_API void joinSink();

    /**
     * @brief This method push data to the sink queue.
     * 
     * @param p_data push data to the sink.
     * @return void
     */
    EXPORTED_API void setData(std::vector<CtBlockDataPtr> p_data);

protected:
    /**
     * @brief Contructor.
     * 
     */
    EXPORTED_API CtSink();

    /**
     * @brief Destructor.
     * 
     */
    EXPORTED_API ~CtSink();

    /**
     * @brief This virtual method writes data to the sink.
     * 
     * @param p_data The data to be added to the queue.
     * @return CtUInt32 event code. 
     */
    EXPORTED_API virtual CtUInt32 write(CtBlockDataPtr& p_data) = 0;

private:

    /**
     * @brief This method is the main loop executed by each sink.
     * 
     */
    void loop() override;
};

#endif //INCLUDE_CTSINK_HPP_