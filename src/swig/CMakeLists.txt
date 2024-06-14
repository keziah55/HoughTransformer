find_package(Python COMPONENTS Development Interpreter)

if (Python_FOUND)
  message(${Python_SITELIB}) # print sitepath
else()
  message("No Python found.")
  return()
endif()

find_package(SWIG)
include(UseSWIG)

if(SWIG_FOUND)
  message("Found SWIG ${SWIG_VERSION}")
else()
  message("No SWIG found.")
  return()
endif()

set(UseSWIG_TARGET_NAME_PREFERENCE STANDARD)

set_property(SOURCE hough.i PROPERTY CPLUSPLUS ON)

message("${CMAKE_SOURCE_DIR}/houghsrc")

include_directories("${CMAKE_SOURCE_DIR}/houghsrc" "${Python_INCLUDE_DIRS}")

# convenience variable
set(hough_build_dir ${CMAKE_CURRENT_BINARY_DIR}/hough)

swig_add_library(hough
  TYPE SHARED
  LANGUAGE python
  OUTPUT_DIR ${hough_build_dir} # important! else find_packages() wont find
  SOURCES hough.i
)

set_property(TARGET hough PROPERTY SUFFIX ".so")
# and again, so that the .so file is in the right place
set_property(TARGET hough PROPERTY LIBRARY_OUTPUT_DIRECTORY ${hough_build_dir})

target_link_libraries(hough PRIVATE houghlib ${Python_LIBRARIES})

# ----------------------- installation specific ----------------------- #

# copy files
configure_file(setup.py ${CMAKE_CURRENT_BINARY_DIR}/setup.py COPYONLY)
configure_file(MANIFEST.in ${CMAKE_CURRENT_BINARY_DIR}/MANIFEST.in COPYONLY)

# and make it a module
install(CODE "file(COPY ${hough_build_dir}/hough.py ${hough_build_dir}/__init__.py)")
# handle with pip
install(
  CODE "execute_process(WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} COMMAND ${Python_EXECUTABLE} -m pip install .)"
)