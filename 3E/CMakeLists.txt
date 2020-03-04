cmake_minimum_required(VERSION 3.13)
project(3E)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(3E
        filter.C
        filter.h
        image.C
        image.h
        main3E.C
        pixel.h
        PNMreader.C
        PNMreader.h
        PNMwriter.C
        PNMwriter.h
        sink.C
        sink.h
        source.C
        source.h)
