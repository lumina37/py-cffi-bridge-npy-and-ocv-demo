find_package(Python COMPONENTS Interpreter Development.Module NumPy REQUIRED)
find_package(OpenCV COMPONENTS core imgproc REQUIRED)

set(FOO_INCLUDE_DIRS "include" ${OpenCV_INCLUDE_DIRS} ${Python_NumPy_INCLUDE_DIRS})
set(FOO_LIBS ${OpenCV_LIBS})
set(FOO_SRCS "src/allocator.cpp" "src/convert.cpp" "src/lib.cpp")

Python_add_library(algofoo MODULE ${FOO_SRCS})
target_include_directories(algofoo PUBLIC ${FOO_INCLUDE_DIRS})
target_link_libraries(algofoo PUBLIC ${FOO_LIBS})

install(TARGETS algofoo DESTINATION ${SKBUILD_PROJECT_NAME}/algorithm)
