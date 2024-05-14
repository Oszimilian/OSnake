cmake_minimum_required(VERSION 3.10)

project(Snake)

find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIR})

file(GLOB SRC *.c)
file(GLOB INC *.h)

add_executable(Snake ${SRC} ${INC})

target_link_libraries(Snake ${CURSES_LIBRARIES})
