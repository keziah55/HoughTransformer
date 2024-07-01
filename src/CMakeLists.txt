message("Using C++ standard: ${CMAKE_CXX_STANDARD}")

set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")

set(houghsrc hough.cxx)

add_library(houghlib STATIC ${houghsrc})

find_package(Python COMPONENTS Development Interpreter)
find_package(SWIG)
include(UseSWIG)

set(UseSWIG_TARGET_NAME_PREFERENCE STANDARD)

set_property(SOURCE hough.i PROPERTY CPLUSPLUS ON)

execute_process(
    COMMAND ${Python_EXECUTABLE} ${CMAKE_SOURCE_DIR}/src/get_numpy_include_path.py
    OUTPUT_VARIABLE NUMPY_INCLUDE
)

if (NOT NUMPY_INCLUDE) 
  message("Could not find NumPy include path")
endif()

include_directories("${CMAKE_SOURCE_DIR}/src" "${Python_INCLUDE_DIRS}" "${NUMPY_INCLUDE}")

# convenience variable
set(hough_build_dir ${CMAKE_CURRENT_BINARY_DIR}/hough)

swig_add_library(hough
  TYPE SHARED
  LANGUAGE python
  OUTPUT_DIR ${hough_build_dir}
  SOURCES hough.i
)

if (gcc_like_cxx)
  set_property(TARGET hough PROPERTY SUFFIX ".so")
elseif (msvc_cxx) 
  set_property(TARGET hough PROPERTY SUFFIX ".dll")
else ()
  message("Unrecognised compiler")
endif()
# and again, so that the .so file is in the right place
set_property(TARGET hough PROPERTY LIBRARY_OUTPUT_DIRECTORY ${hough_build_dir})

target_link_libraries(hough PRIVATE houghlib ${Python_LIBRARIES})

# ----------------------- installation specific ----------------------- #

# copy files
configure_file(setup.py ${CMAKE_CURRENT_BINARY_DIR}/setup.py COPYONLY)
configure_file(__init__.py ${hough_build_dir}/__init__.py COPYONLY)
configure_file(MANIFEST.in ${CMAKE_CURRENT_BINARY_DIR}/MANIFEST.in COPYONLY)
