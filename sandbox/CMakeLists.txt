cmake_minimum_required(VERSION 3.13)
project(proj3G)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(
        logging.h logging.cpp source.h image.cpp image.h filter.h filter.cpp source.h source.cpp sink.h sink.cpp PNMreader.h PNMreader.cpp PNMwriter.h PNMwriter.cpp main3G.cpp)