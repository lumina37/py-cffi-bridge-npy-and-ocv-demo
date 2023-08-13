find_package(Python COMPONENTS Interpreter Development.Module REQUIRED)

Python_add_library(_algorithm MODULE "./src/lib.c" WITH_SOABI)
install(TARGETS _algorithm DESTINATION ${SKBUILD_PROJECT_NAME}/algorithm)
