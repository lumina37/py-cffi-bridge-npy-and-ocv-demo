find_package(PythonExtensions REQUIRED)

add_library(foo MODULE "./src/lib.c")
python_extension_module(foo)
install(TARGETS foo LIBRARY DESTINATION ".")
