cmake_minimum_required(VERSION 3.22)
project(cpptoolkit)

set(CMAKE_CXX_STANDARD 20)

if(MSVC)
    # Visual Studio
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Od /Zi")
    set(TARGET_LIBRARY cpptoolkit)
    add_compile_options(/FS)
else()
    # GCC or Clang
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -fsanitize=address")
    set(TARGET_LIBRARY cpptoolkit)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(-fsanitize=address)
        add_link_options(-fsanitize=address)
    endif()
endif()

set(ROOT_DIR ${CMAKE_SOURCE_DIR})
set(INCLUDE_DIR ${ROOT_DIR}/include/)
set(SOURCE_DIR ${ROOT_DIR}/src/)
set(EXAMPLES_DIR ${ROOT_DIR}/examples/)
set(TESTS_DIR ${ROOT_DIR}/tests/)

# Specify the output directory for the build artifacts
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(${INCLUDE_DIR})

# Library Build
add_library(${TARGET_LIBRARY} SHARED
    ${SOURCE_DIR}/io/CtLogger.cpp
    ${SOURCE_DIR}/io/CtConfigParser.cpp
    ${SOURCE_DIR}/io/sinks/CtFileSink.cpp
    ${SOURCE_DIR}/io/sinks/CtLogSink.cpp
    ${SOURCE_DIR}/io/sinks/CtSink.cpp
    ${SOURCE_DIR}/time/CtTimer.cpp
    ${SOURCE_DIR}/utils/CtTask.cpp
    ${SOURCE_DIR}/threading/CtThread.cpp
    ${SOURCE_DIR}/threading/CtService.cpp
    ${SOURCE_DIR}/threading/CtServicePool.cpp
    ${SOURCE_DIR}/threading/CtWorker.cpp
    ${SOURCE_DIR}/threading/CtWorkerPool.cpp
    ${SOURCE_DIR}/networking/sockets/CtSocketHelpers.cpp
    ${SOURCE_DIR}/networking/sockets/CtSocketUdp.cpp
)

# Examples Build
add_executable(ex01_worker ${EXAMPLES_DIR}/ex01_worker.cpp)
target_link_libraries(ex01_worker ${TARGET_LIBRARY})

add_executable(ex02_worker_pool ${EXAMPLES_DIR}/ex02_worker_pool.cpp)
target_link_libraries(ex02_worker_pool ${TARGET_LIBRARY})

add_executable(ex03_service ${EXAMPLES_DIR}/ex03_service.cpp)
target_link_libraries(ex03_service ${TARGET_LIBRARY})

add_executable(ex04_service_pool ${EXAMPLES_DIR}/ex04_service_pool.cpp)
target_link_libraries(ex04_service_pool ${TARGET_LIBRARY})

add_executable(ex05_config ${EXAMPLES_DIR}/ex05_config.cpp)
target_link_libraries(ex05_config ${TARGET_LIBRARY})

add_executable(ex06_logger ${EXAMPLES_DIR}/ex06_logger.cpp)
target_link_libraries(ex06_logger ${TARGET_LIBRARY})

# Testing
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.11.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(test_ctlogger ${TESTS_DIR}/ctlogger.cpp ${TESTS_DIR}/main_test.cpp)
target_link_libraries(test_ctlogger ${TARGET_LIBRARY} gtest_main)

add_test(NAME CtLoggerTests COMMAND test_ctlogger)

add_executable(test_configparser ${TESTS_DIR}/ctconfigparser.cpp ${TESTS_DIR}/main_test.cpp)
target_link_libraries(test_configparser ${TARGET_LIBRARY} gtest_main)

add_test(NAME CtConfigParserTests COMMAND test_configparser)

add_executable(test_ctservice ${TESTS_DIR}/ctservice.cpp ${TESTS_DIR}/main_test.cpp)
target_link_libraries(test_ctservice ${TARGET_LIBRARY} gtest_main)

add_test(NAME CtServiceTests COMMAND test_ctservice)

add_executable(test_ctservicepool ${TESTS_DIR}/ctservicepool.cpp ${TESTS_DIR}/main_test.cpp)
target_link_libraries(test_ctservicepool ${TARGET_LIBRARY} gtest_main)

add_test(NAME CtServicePoolTests COMMAND test_ctservicepool)

add_executable(test_ctworker ${TESTS_DIR}/ctworker.cpp ${TESTS_DIR}/main_test.cpp)
target_link_libraries(test_ctworker ${TARGET_LIBRARY} gtest_main)

add_test(NAME CtWorkerTests COMMAND test_ctworker)

add_executable(test_ctworkerpool ${TESTS_DIR}/ctworkerpool.cpp ${TESTS_DIR}/main_test.cpp)
target_link_libraries(test_ctworkerpool ${TARGET_LIBRARY} gtest_main)

add_test(NAME CtWorkerPoolTests COMMAND test_ctworkerpool)

if(MSVC)
    target_compile_definitions(${TARGET_LIBRARY} PRIVATE _WIN32)
else()
    target_compile_definitions(${TARGET_LIBRARY} PRIVATE _UNIX)
endif()
