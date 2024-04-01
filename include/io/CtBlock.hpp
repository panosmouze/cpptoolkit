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
 * @file CtBlock.hpp
 * @brief 
 * @date 06-03-2024
 * 
 */

#ifndef INCLUDE_CTBLOCK_HPP_
#define INCLUDE_CTBLOCK_HPP_

#include "definitions.hpp"

#include "io/CtBlockType.hpp"
#include "io/CtBlockData.hpp"

#include "utils/CtObject.hpp"

#include <vector>
#include <queue>

class CtBlock : public CtObject {
public:
    /**
     * @brief This method returns the in-vector size.
     * 
     * @return CtUInt32 the size of the input vector.
     */
    EXPORTED_API CtUInt32 getInVectorSize();

    /**
     * @brief This method retuns the accepted input types for this block.
     * 
     * @return std::vector<CtBlockDataType> Vector containg the accepted input data types.
     */
    EXPORTED_API std::vector<CtBlockDataType> getInVectorTypes();

    /**
     * @brief This method returns the out-vector size.
     * 
     * @return CtUInt32 the size of the output vector.
     */
    EXPORTED_API CtUInt32 getOutVectorSize();

    /**
     * @brief This method retuns the accepted output types for this block.
     * 
     * @return std::vector<CtBlockDataType> Vector containg the accepted output data types.
     */
    EXPORTED_API std::vector<CtBlockDataType> getOutVectorTypes();

    /**
     * @brief This virtual method is implemented by each block according to the functionality it serves.
     * 
     * @return void
     */
    EXPORTED_API virtual void process();

protected:
    /**
     * @brief CtBlock contructor.
     * 
     */
    EXPORTED_API CtBlock();

    /**
     * @brief CtBlock destructor.
     * 
     */
    EXPORTED_API ~CtBlock();

    /**
     * @brief Set the input vector accepted types.
     * 
     * @param p_inTypes the input vector accepted types.
     * @return void
     */
    EXPORTED_API void setInVectorTypes(std::vector<CtBlockDataType> p_inTypes);

    /**
     * @brief Returns true if this block has available data to consume.
     * 
     * @return bool True if has data. False if there is no data in the input buffer.
     */
    EXPORTED_API bool hasInData();

    /**
     * @brief Push data to the input queue.
     * 
     * @param p_data push data to the input vector.
     * @return void
     */
    EXPORTED_API void setInData(std::vector<CtBlockDataPtr> p_data);

    /**
     * @brief Pop data from the input vector if available.
     * 
     * @return std::vector<CtBlockDataPtr> the next available input vector data.
     */
    EXPORTED_API std::vector<CtBlockDataPtr> getInData();

    /**
     * @brief Set the output vector accepted types.
     * 
     * @param p_inTypes the output vector accepted types.
     * @return void
     */
    EXPORTED_API void setOutVectorTypes(std::vector<CtBlockDataType> p_outTypes);

    /**
     * @brief Returns true if this block has available data to return.
     * 
     * @return bool True if has data. False if there is no data in the output buffer.
     */
    EXPORTED_API bool hasOutData();

    /**
     * @brief Push data to the output queue.
     * 
     * @param p_data push data to the output vector.
     * @return void
     */
    EXPORTED_API void setOutData(std::vector<CtBlockDataPtr> p_data);

    /**
     * @brief Pop data from the output queue.
     * 
     * @return std::vector<CtBlockDataPtr> the next available output vector data.
     * @return void
     */
    EXPORTED_API std::vector<CtBlockDataPtr> getOutData();

private:
    std::mutex m_mtx_out; ///< Mutex for controlling access to output resources.
    std::mutex m_mtx_in; ///< Mutex for controlling access to input resources.
    std::vector<CtBlockDataType> m_inTypes; ///< input vector accepted types.
    std::vector<CtBlockDataType> m_outTypes; ///< output vector accepted types.
    std::queue<std::vector<CtBlockDataPtr>> m_inData; ///< input queue.
    std::queue<std::vector<CtBlockDataPtr>> m_outData; ///< output queue.
};

#endif //INCLUDE_CTBLOCK_HPP_