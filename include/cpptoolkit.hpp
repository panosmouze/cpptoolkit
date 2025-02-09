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
 * @file cpptoolkit.hpp
 * @brief Master header file for the C++ Toolkit library.
 * @date 10-01-2025
 * 
 */

#ifndef INCLUDE_CPPTOOLKIT_HPP_
#define INCLUDE_CPPTOOLKIT_HPP_

/** 
 * Include basic header files
 * 
 */
#include "core.hpp"

/**
 * Include objects related to IO
 * 
 */
#include "io/CtFileInput.hpp"
#include "io/CtFileOutput.hpp"

/**
 * Include objects related to networking
 * 
 */
#include "networking/CtSocketUdp.hpp"

/**
 * Include objects related to threading
 * 
 */
#include "threading/CtTask.hpp"
#include "threading/CtThread.hpp"
#include "threading/CtWorker.hpp"
#include "threading/CtWorkerPool.hpp"
#include "threading/CtService.hpp"
#include "threading/CtServicePool.hpp"

/**
 * Include objects related to time management
 * 
 */
#include "time/CtTimer.hpp"

/**
 * Include objects related to utils
 * 
 */
#include "utils/CtConfig.hpp"
#include "utils/CtLogger.hpp"
#include "utils/CtObject.hpp"

#endif //INCLUDE_CPPTOOLKIT_HPP_