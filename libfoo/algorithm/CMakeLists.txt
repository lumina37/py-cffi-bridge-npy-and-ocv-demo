find_package(Python3 COMPONENTS Interpreter Development.Module NumPy REQUIRED)
find_package(OpenCV COMPONENTS core imgproc REQUIRED)

set(_algorithm_INCLUDE_DIRS "include" ${OpenCV_INCLUDE_DIRS} ${Python3_NumPy_INCLUDE_DIRS})
set(_algorithm_LIBS ${OpenCV_LIBS})
set(_algorithm_SRCS "src/allocator.cpp" "src/convert.cpp" "src/lib.cpp")

Python3_add_library(_algorithm MODULE ${_algorithm_SRCS} WITH_SOABI)
target_include_directories(_algorithm PUBLIC ${_algorithm_INCLUDE_DIRS})
target_link_libraries(_algorithm PUBLIC ${_algorithm_LIBS})
target_compile_features(_algorithm PUBLIC cxx_std_11)

install(TARGETS _algorithm DESTINATION ${SKBUILD_PROJECT_NAME}/algorithm)
