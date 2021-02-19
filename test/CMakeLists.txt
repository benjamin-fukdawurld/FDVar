cmake_minimum_required(VERSION 3.10)

project("FDVar_test" VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra")

set(FDVAR_GTEST_DIR "" CACHE PATH "path to googletest root directory")

set(GTEST_ROOT ${FDVAR_GTEST_DIR})
if(NOT DEFINED GTEST_ROOT)
    message(STATUS "GTEST_ROOT not defined: using default path")
else()
    set(GTest_ROOT ${GTEST_ROOT})
    set(GTest_INCLUDE_DIR ${GTest_ROOT}/include)
    set(GTest_LIBRARIES ${GTest_ROOT}/lib)
    if(NOT GTEST_INCLUDE_DIR)
        set(GTEST_INCLUDE_DIR ${GTEST_ROOT}/include)
    endif()

    if(NOT GTEST_LIBRARIES)
        set(GTEST_LIBRARIES ${GTEST_ROOT}/lib)
    endif()
endif()

enable_testing()
if(NOT GTEST_FOUND)
    find_package(GTest REQUIRED COMPONENTS gtest)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
endif()

set(TEST_HEADER_FILES
    FDVar/ArrayValue_test.h
    FDVar/BoolValue_test.h
    FDVar/DynamicVariable_test.h
    FDVar/FloatValue_test.h
    FDVar/FunctionValue_test.h
    FDVar/IntValue_test.h
    FDVar/ObjectValue_test.h
    FDVar/StringValue_test.h
)

add_executable(${PROJECT_NAME} main.cpp)

set_property(TARGET ${PROJECT_NAME} PROPERTY ENABLE_EXPORTS 1)

target_include_directories(${PROJECT_NAME}
                            PUBLIC ../include
                            PUBLIC ${GTEST_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} Threads::Threads)
target_link_libraries(${PROJECT_NAME} GTest::GTest)
target_link_libraries(${PROJECT_NAME} dl)
target_link_libraries(${PROJECT_NAME} FDVar)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
