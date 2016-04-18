
cmake_minimum_required (VERSION 2.8.8)
project (sdl-grapher C)
find_package (SDL)

set (libsrc graph.c)

# this is the "object library" target: compiles the sources only once
add_library (objlib OBJECT ${libsrc})

# shared libraries need PIC
set_property (TARGET objlib PROPERTY POSITION_INDEPENDENT_CODE 1)

# actual shared and static libraries built from the same object files
add_library (sdlgrapher SHARED $<TARGET_OBJECTS:objlib>)
add_library (sdlgrapher_static STATIC $<TARGET_OBJECTS:objlib>)

# the example program
add_executable (example example.c)
set (CMAKE_INCLUDE_CURRENT_DIR ON)
target_link_libraries (example sdlgrapher_static ${SDL_LIBRARY} m)
