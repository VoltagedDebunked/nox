cmake_minimum_required(VERSION 3.10)
project(Nox)

set(CMAKE_C_STANDARD 11)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK REQUIRED gtk+-3.0 vte-2.91)

include_directories(${GTK_INCLUDE_DIRS})
link_directories(${GTK_LIBRARY_DIRS})

add_executable(nox src/main.c)
target_link_libraries(nox ${GTK_LIBRARIES})

add_definitions(${GTK_CFLAGS_OTHER})