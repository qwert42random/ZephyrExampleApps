# Declare current directory as zephyr library.
# If no name is given, name is derived from directory name.
zephyr_library()

# List source code files for library.
zephyr_library_sources(src/test.c)

# Add header files to CMake search directories.
zephyr_include_directories(inc)
