cmake_minimum_required(VERSION 3.25)
project(Plotter)

set(CMAKE_CXX_STANDARD 20)

set(SOURCES
        Canvas.hpp
        CanvasIterators.hpp
        Canvas.cpp
        Plotter.cpp
        Plotter.hpp
        GrayscalePlotter.cpp
        GrayscalePlotter.hpp
        Config.cpp
        Canvas.hpp
        DemoRunner.cpp
        DemoRunner.hpp
        json.cpp
        json.h
        main.cpp
        Timer.cpp
        Timer.hpp
)

add_executable(Plotter ${SOURCES})
