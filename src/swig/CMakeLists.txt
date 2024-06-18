find_package(Python COMPONENTS Development Interpreter)
find_package(SWIG)
include(UseSWIG)

set(UseSWIG_TARGET_NAME_PREFERENCE STANDARD)

set_property(SOURCE hough.i PROPERTY CPLUSPLUS ON)

execute_process(
    COMMAND ${Python_EXECUTABLE} ${CMAKE_SOURCE_DIR}/src/swig/get_numpy_include_path.py
    OUTPUT_VARIABLE NUMPY_INCLUDE
)

if (NOT NUMPY_INCLUDE) 
  message("Could not find NumPy include path")
endif()

include_directories("${CMAKE_SOURCE_DIR}/src" "${Python_INCLUDE_DIRS}" "${NUMPY_INCLUDE}")

# convenience variable
set(hough_build_dir ${CMAKE_CURRENT_BINARY_DIR}/hough)

message("${hough_build_dir}")

swig_add_library(hough
  TYPE SHARED
  LANGUAGE python
  OUTPUT_DIR ${hough_build_dir}
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