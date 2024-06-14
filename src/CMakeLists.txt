
message("Standard: ${CMAKE_CXX_STANDARD}")

set(houghsrc hough.cxx)

add_library(houghlib STATIC ${houghsrc})

add_subdirectory(swig)