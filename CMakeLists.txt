cmake_minimum_required(VERSION 3.10)

project("FDVar" VERSION 0.1)

configure_file(include/FDVar/FDVarConfig.h.in FDVarConfig.h)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra")

option(FDVAR_BUILD_STATIC "Build FDVar as static library" OFF)

option(FDVAR_BUILD_TESTS "Build FDVar tests" ON)

set(HEADER_FILES
    include/FDVar/AbstractArrayValue.h
    include/FDVar/AbstractObjectValue.h
    include/FDVar/AbstractValue.h
    include/FDVar/ArrayValue.h
    include/FDVar/BoolValue.h
    include/FDVar/DynamicVariable_fwd.h
    include/FDVar/DynamicVariable.h
    include/FDVar/FloatValue.h
    include/FDVar/FunctionValue.h
    include/FDVar/IntValue.h
    include/FDVar/ObjectValue.h
    include/FDVar/StringValue.h
    include/FDVar/ValueType.h
)

set(SRC_FILES
    src/DynamicVariable.cpp
    src/ArrayValue.cpp
)

if(FDVAR_BUILD_STATIC)
    add_library(${PROJECT_NAME} STATIC ${SRC_FILES} ${HEADER_FILES})
else()
    add_library(${PROJECT_NAME} SHARED ${SRC_FILES} ${HEADER_FILES})
endif()

target_include_directories(${PROJECT_NAME}
                            PUBLIC include)

if(FDVAR_BUILD_TESTS)
    add_subdirectory(test)
endif()
