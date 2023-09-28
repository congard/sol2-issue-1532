cmake_minimum_required(VERSION 3.20)
project(sol2_issue_1532)

set(CMAKE_CXX_STANDARD 17)

message(STATUS "CMAKE_C_COMPILER: ${CMAKE_C_COMPILER}")
message(STATUS "CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")

if (UNIX)
    message(STATUS "Unix")
    add_compile_options(-fPIC)
elseif (WIN32)
    message(STATUS "Windows")
else()
    message(FATAL_ERROR "Unsupported OS")
endif()

add_subdirectory(contrib/lua)
add_subdirectory(contrib/sol2)

set(EXE_NAME sol2_issue_1532)
set(LIB_NAME sol2_issue_1532_lib)

if (NOT DEFINED LIB_TYPE)
    set(LIB_TYPE SHARED)
endif()

message(STATUS "Library type: ${LIB_TYPE}")

add_library(${LIB_NAME} ${LIB_TYPE}
        src/lib/platform.h
        src/lib/Foo.cpp
        src/lib/Foo.h
        src/lib/Bar.cpp
        src/lib/Bar.h
        src/lib/Lua.cpp
        src/lib/Lua.h)

target_link_libraries(${LIB_NAME} PUBLIC lua_static)

if (WIN32 AND "${LIB_TYPE}" STREQUAL "SHARED")
    target_compile_definitions(${LIB_NAME} PRIVATE EXPORT_API_SYMBOLS)
elseif (WIN32)
    target_compile_definitions(${LIB_NAME} PUBLIC STATIC_LIB)
endif()

target_include_directories(${LIB_NAME} PUBLIC
        contrib/lua/lua-5.4.6/include
        contrib/sol2/include)

add_executable(${EXE_NAME} src/main.cpp)
target_link_libraries(${EXE_NAME} PRIVATE ${LIB_NAME})