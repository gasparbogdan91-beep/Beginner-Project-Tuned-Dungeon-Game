cmake_minimum_required(VERSION 3.12)
project(project1)

set(CMAKE_CXX_STANDARD 23)

# 1. Automatically find all your .cpp and .h game files
file(GLOB CORE_SOURCES "*.cpp" "*.h")

# 2. Add raylib as a direct source subdirectory and build it automatically
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # Disables extra examples
add_subdirectory("C:/raylib/raylib" "${CMAKE_BINARY_DIR}/raylib_build")

# 3. Create your executable target using your game files
add_executable(1 ${CORE_SOURCES})

# 4. Map the source folder headers so your code editor finds #include "raylib.h"
target_include_directories(1 PRIVATE "C:/raylib/raylib/src")

# 5. Link the newly compiled raylib target and Windows system frameworks
target_link_libraries(1 PRIVATE raylib winmm gdi32 user32 shell32)

# 6. Apply proper Visual Studio MSVC compiler flags
if(MSVC)
    target_compile_options(1 PRIVATE /W4) # High warning level for Visual Studio
else()
    target_compile_options(1 PRIVATE -Wall -Wextra) # Fallback for GCC/Clang
endif()

