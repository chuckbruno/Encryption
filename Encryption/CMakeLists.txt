# CMakeList.txt : CMake project for Encryption, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable(Encryption "Encryption.cpp" "Encryption.h" "EncryptorEngine.h" "EncryptorEngine.cpp" "common.h" "common.cpp")

# TODO: Add tests and install targets if needed.
