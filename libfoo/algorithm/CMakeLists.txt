find_package(PythonExtensions REQUIRED)

add_library(_algorithm MODULE "./src/lib.c")
python_extension_module(_algorithm)
install(TARGETS _algorithm LIBRARY DESTINATION "libfoo/algorithm")
