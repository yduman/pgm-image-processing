cmake_minimum_required(VERSION 2.4)

set(EXECUTABLE_OUTPUT_PATH "./out")

project(PGM_IMAGE_PROCESSING)

if(NOT MSVC)
   set(CMAKE_C_FLAGS "-std=c11")
endif()

set(CMAKE_VERBOSE_MAKEFILE on)

# A1
set(SOURCES_A1
        src/p1.c
        src/pgm.c
        src/pgm.h)
add_executable(p1 ${SOURCES_A1})
target_link_libraries(p1 m)

# A2
set(SOURCES_A2
        src/p2.c
        src/pgm.c
        src/pgm.h)
add_executable(p2 ${SOURCES_A2})
target_link_libraries(p2 m)

# A3
set(SOURCES_A3
        src/p3.c
        src/pgm.c
        src/pgm.h)
add_executable(p3 ${SOURCES_A3})
target_link_libraries(p3 m)

# A4
set(SOURCES_A4
        src/p4.c
        src/pgm.c
        src/pgm.h)
add_executable(p4 ${SOURCES_A4})
target_link_libraries(p4 m)
