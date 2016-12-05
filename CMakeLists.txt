cmake_minimum_required(VERSION 2.8)
project(signed_size)
enable_testing()

set(WARNINGS)

option(BUILD_TESTS "Build tests." ON)

# Compiler
if(${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
  message("-- Setting clang options")
  set(WARNINGS "-Wall -Wextra")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
  set(STRICT_CXX_FLAGS ${WARNINGS} "-Werror -pedantic")
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
  message("-- Setting gcc options")
  set(WARNINGS "-Wall -Wextra")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fno-strict-aliasing")
  set(STRICT_CXX_FLAGS ${WARNINGS} "-Werror -pedantic")
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
  message("-- Setting msvc options")
else()
  message("-- Unknown compiler, success is doubtful.")
endif()

# Reconfigure final output directory
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

include_directories(include)

if(BUILD_TESTS)
  add_subdirectory(test)
endif()

