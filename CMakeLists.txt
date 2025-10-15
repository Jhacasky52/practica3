cmake_minimum_required(VERSION 3.16)

project(practica4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(practica4 main.cpp
    funciones.h
    funciones.cpp)

include(GNUInstallDirs)
install(TARGETS practica4
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
