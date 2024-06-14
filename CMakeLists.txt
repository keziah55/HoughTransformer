cmake_minimum_required(VERSION 3.15)

project(hough VERSION 1.0.1 DESCRIPTION "Hough transform library")

include(GNUInstallDirs)

include_directories(/usr/include/python3.11 /usr/lib/python3/dist-packages/numpy/core/include/)

add_library(hough SHARED src/hough.cxx)
add_library(hough_wrap SHARED src/hough_wrap.cxx)

set_target_properties(hough PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    PUBLIC_HEADER api/hough.h)

configure_file(hough.pc.in hough.pc @ONLY)

target_include_directories(hough PRIVATE .)

install(TARGETS hough
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(FILES ${CMAKE_BINARY_DIR}/hough.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)