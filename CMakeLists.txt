cmake_minimum_required(VERSION 2.6)

PROJECT(mysuperdemo)

SET(NESTK_USE_FREENECT 0)
SET(NESTK_USE_OPENNI 1)
ADD_SUBDIRECTORY(nestk)
## nestk/UseNestk.cmake.in defines variable to use nestk.
## It itself includes nestk/deps/cmake/UseEmbeddedNestkDeps.cmake that
## contains most of the cmake find packages commands.
INCLUDE("${nestk_BINARY_DIR}/UseEmbeddedNestk.cmake")

ADD_EXECUTABLE(mysuperdemo mysuperdemo.cpp)
TARGET_LINK_LIBRARIES(mysuperdemo nestk)
