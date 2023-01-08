# CMakeList.txt : CMake project for Encryption, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)


SET(ZLIB_PATH "${CMAKE_SOURCE_DIR}/thirdParty/zlib/include")
SET(ZLIB_LIBRARY_DIR "${CMAKE_SOURCE_DIR}/thirdParty/zlib/lib")

INCLUDE_DIRECTORIES(${ZLIB_PATH})
# INCLUDE_DIRECTORIES(${ENCRY_HEADERS_DIR})
LINK_DIRECTORIES(${ZLIB_LIBRARY_DIR})
# Add source to this project's executable.

add_executable(Encryption "Encryption.cpp" "Encryption.h" "EncryptorEngine.h" "EncryptorEngine.cpp" "common.h" "common.cpp")
TARGET_LINK_LIBRARIES(Encryption zlibstat.lib)

# TODO: Add tests and install targets if needed.
