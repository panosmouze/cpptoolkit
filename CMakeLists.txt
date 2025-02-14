cmake_minimum_required(VERSION 3.22)
project(cpptoolkit)

set(CMAKE_CXX_STANDARD 20)

set(TARGET_LIBRARY cpptoolkit)

if(NOT CMAKE_TOOLCHAIN_FILE)
    message(STATUS "No toolchain file specified! Use -DCMAKE_TOOLCHAIN_FILE=<path> when running CMake.")
else()
    message(STATUS "Using toolchain: ${CMAKE_TOOLCHAIN_FILE}")
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -fsanitize=address")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-fsanitize=address)
    add_link_options(-fsanitize=address)
endif()

if(CMAKE_CROSSCOMPILING)
    set(TESTS_ENABLED OFF)
else()
    set(TESTS_ENABLED ON)
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
    ${SOURCE_DIR}/core/CtTypes.cpp
    ${SOURCE_DIR}/core/CtHelpers.cpp
    ${SOURCE_DIR}/io/CtFileOutput.cpp
    ${SOURCE_DIR}/io/CtFileInput.cpp
    ${SOURCE_DIR}/time/CtTimer.cpp
    ${SOURCE_DIR}/utils/CtObject.cpp
    ${SOURCE_DIR}/utils/CtConfig.cpp
    ${SOURCE_DIR}/utils/CtLogger.cpp
    ${SOURCE_DIR}/threading/CtTask.cpp
    ${SOURCE_DIR}/threading/CtThread.cpp
    ${SOURCE_DIR}/threading/CtService.cpp
    ${SOURCE_DIR}/threading/CtServicePool.cpp
    ${SOURCE_DIR}/threading/CtWorker.cpp
    ${SOURCE_DIR}/threading/CtWorkerPool.cpp
    ${SOURCE_DIR}/networking/CtSocketUdp.cpp
)

# Install library files
install(TARGETS ${TARGET_LIBRARY}
    LIBRARY DESTINATION ${CMAKE_BINARY_DIR}/out/lib
    ARCHIVE DESTINATION ${CMAKE_BINARY_DIR}/out/lib
)

# Install header files
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION ${CMAKE_BINARY_DIR}/out/include)

# Examples Build
add_executable(ex01_worker ${EXAMPLES_DIR}/ex01_worker.cpp)
target_link_libraries(ex01_worker ${TARGET_LIBRARY})

add_executable(ex02_worker_pool ${EXAMPLES_DIR}/ex02_worker_pool.cpp)
target_link_libraries(ex02_worker_pool ${TARGET_LIBRARY})

add_executable(ex03_service ${EXAMPLES_DIR}/ex03_service.cpp)
target_link_libraries(ex03_service ${TARGET_LIBRARY})

add_executable(ex04_service_pool ${EXAMPLES_DIR}/ex04_service_pool.cpp)
target_link_libraries(ex04_service_pool ${TARGET_LIBRARY})

add_executable(ex05_events ${EXAMPLES_DIR}/ex05_events.cpp)
target_link_libraries(ex05_events ${TARGET_LIBRARY})

add_executable(ex06_networking_udp ${EXAMPLES_DIR}/ex06_networking_udp.cpp)
target_link_libraries(ex06_networking_udp ${TARGET_LIBRARY})

add_executable(ex07_config ${EXAMPLES_DIR}/ex07_config.cpp)
target_link_libraries(ex07_config ${TARGET_LIBRARY})

add_executable(ex08_logger ${EXAMPLES_DIR}/ex08_logger.cpp)
target_link_libraries(ex08_logger ${TARGET_LIBRARY})

# Testing
if(TESTS_ENABLED)
    find_package(GTest REQUIRED)

    enable_testing()

    add_executable(test_cttypes ${TESTS_DIR}/cttypes.cpp ${TESTS_DIR}/main_test.cpp)
    target_link_libraries(test_cttypes ${TARGET_LIBRARY} gtest_main ${GTEST_BOTH_LIBRARIES})
    target_include_directories( test_cttypes PRIVATE ${GTEST_INCLUDE_DIRS} )
    add_test(NAME CtTypes COMMAND test_cttypes)

    add_executable(test_ctfile ${TESTS_DIR}/ctfile.cpp ${TESTS_DIR}/main_test.cpp)
    target_link_libraries(test_ctfile ${TARGET_LIBRARY} gtest_main ${GTEST_BOTH_LIBRARIES})
    target_include_directories( test_ctfile PRIVATE ${GTEST_INCLUDE_DIRS} )
    add_test(NAME CtFile COMMAND test_ctfile)

    add_executable(test_cttask ${TESTS_DIR}/cttask.cpp ${TESTS_DIR}/main_test.cpp)
    target_link_libraries(test_cttask ${TARGET_LIBRARY} gtest_main ${GTEST_BOTH_LIBRARIES})
    target_include_directories( test_cttask PRIVATE ${GTEST_INCLUDE_DIRS} )
    add_test(NAME CtTask COMMAND test_cttask)

    add_executable(test_ctthread ${TESTS_DIR}/ctthread.cpp ${TESTS_DIR}/main_test.cpp)
    target_link_libraries(test_ctthread ${TARGET_LIBRARY} gtest_main ${GTEST_BOTH_LIBRARIES})
    target_include_directories( test_ctthread PRIVATE ${GTEST_INCLUDE_DIRS} )
    add_test(NAME CtThread COMMAND test_ctthread)

    add_executable(test_ctworker ${TESTS_DIR}/ctworker.cpp ${TESTS_DIR}/main_test.cpp)
    target_link_libraries(test_ctworker ${TARGET_LIBRARY} gtest_main ${GTEST_BOTH_LIBRARIES})
    target_include_directories( test_ctworker PRIVATE ${GTEST_INCLUDE_DIRS} )
    add_test(NAME CtWorker COMMAND test_ctworker)

    add_executable(test_ctworkerpool ${TESTS_DIR}/ctworkerpool.cpp ${TESTS_DIR}/main_test.cpp)
    target_link_libraries(test_ctworkerpool ${TARGET_LIBRARY} gtest_main ${GTEST_BOTH_LIBRARIES})
    target_include_directories( test_ctworkerpool PRIVATE ${GTEST_INCLUDE_DIRS} )
    add_test(NAME CtWorkerPool COMMAND test_ctworkerpool)

    add_executable(test_ctservice ${TESTS_DIR}/ctservice.cpp ${TESTS_DIR}/main_test.cpp)
    target_link_libraries(test_ctservice ${TARGET_LIBRARY} gtest_main ${GTEST_BOTH_LIBRARIES})
    target_include_directories( test_ctservice PRIVATE ${GTEST_INCLUDE_DIRS} )
    add_test(NAME CtService COMMAND test_ctservice)

    add_executable(test_ctservicepool ${TESTS_DIR}/ctservicepool.cpp ${TESTS_DIR}/main_test.cpp)
    target_link_libraries(test_ctservicepool ${TARGET_LIBRARY} gtest_main ${GTEST_BOTH_LIBRARIES})
    target_include_directories( test_ctservicepool PRIVATE ${GTEST_INCLUDE_DIRS} )
    add_test(NAME CtServicePool COMMAND test_ctservicepool)

    add_executable(test_cttimer ${TESTS_DIR}/cttimer.cpp ${TESTS_DIR}/main_test.cpp)
    target_link_libraries(test_cttimer ${TARGET_LIBRARY} gtest_main ${GTEST_BOTH_LIBRARIES})
    target_include_directories( test_cttimer PRIVATE ${GTEST_INCLUDE_DIRS} )
    add_test(NAME CtTimer COMMAND test_cttimer)

    add_executable(test_ctconfig ${TESTS_DIR}/ctconfig.cpp ${TESTS_DIR}/main_test.cpp)
    target_link_libraries(test_ctconfig ${TARGET_LIBRARY} gtest_main ${GTEST_BOTH_LIBRARIES})
    target_include_directories( test_ctconfig PRIVATE ${GTEST_INCLUDE_DIRS} )
    add_test(NAME CtConfig COMMAND test_ctconfig)

    add_executable(test_ctobject ${TESTS_DIR}/ctobject.cpp ${TESTS_DIR}/main_test.cpp)
    target_link_libraries(test_ctobject ${TARGET_LIBRARY} gtest_main ${GTEST_BOTH_LIBRARIES})
    target_include_directories( test_ctobject PRIVATE ${GTEST_INCLUDE_DIRS} )
    add_test(NAME CtObject COMMAND test_ctobject)
endif()

target_compile_definitions(${TARGET_LIBRARY} PRIVATE _UNIX)
