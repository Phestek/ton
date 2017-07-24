cmake_minimum_required(VERSION 3.6)
project(ton CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g -DTON_DEBUG=1")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3 -DTON_DEBUG=0 -DNDEBUG")

if(NOT DEFINED ${CMAKE_BUILD_TYPE})
    set(CMAKE_BUILD_TYPE "Debug")
endif()
if(NOT DEFINED ${TON_STATIC})
    set(TON_BUILD_STATIC true)
endif()
if(NOT DEFINED ${TON_NO_TESTS})
    set(TON_NO_TESTS false)
endif()

set(HEADERS
        include/ton/document.h
        include/ton/element.h)
set(SOURCES
        src/ton/document.cc
        src/ton/element.cc
        src/ton/lexer.cc
        src/ton/lexer.h
        src/ton/parser.cc
        src/ton/parser.h)
if(TON_STATIC)
    add_library(ton STATIC ${HEADERS} ${SOURCES})
else()
    add_library(ton SHARED ${HEADERS} ${SOURCES})
endif()
target_include_directories(ton PUBLIC include src)

if(NOT TON_NO_TESTS)
    enable_testing()
    set(TESTS
            test/element_tests.cc
            test/lexer_tests.cc
            test/main.cc
            test/parser_test.cc)
    add_executable(ton_tests ${TESTS})
    find_package(GTest REQUIRED)
    target_include_directories(ton_tests PUBLIC ${GTEST_INCLUDE_DIRS})
    target_link_libraries(ton_tests ton ${GTEST_BOTH_LIBRARIES})
    add_test(NAME test_all_in_ton COMMAND ton_tests)
endif()

