cmake_minimum_required(VERSION 3.13)
project(3Eultimate)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(
        source.h image.cpp image.h filter.h filter.cpp source.h source.cpp sink.h sink.cpp PNMreader.h PNMreader.cpp PNMwriter.h PNMwriter.cpp main3F.cpp logging.cpp)
