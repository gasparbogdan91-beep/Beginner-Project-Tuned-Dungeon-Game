cmake_minimum_required(VERSION 3.15)
project(project1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define your executable target
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Character.cpp
    src/Character.h
    src/Config.h
    src/RollRNG.h
    src/MonsterTable.h
    src/Combat.cpp
    src/Combat.h
    src/Boon.cpp
    src/Boon.h
    src/SkillId.h
    
    gui/gui.h
    gui/gui.cpp
)

# 1. Provide search directories for header files
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/gui")

# 2. Look for the static library inside the repo's thirdparty/lib folder
find_library(RAYLIB_LIBRARY_PATH
    NAMES raylib
    PATHS "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/lib"
    NO_DEFAULT_PATH
)

# 3. Link the found raylib library and explicit Windows system dependencies
target_link_libraries(${PROJECT_NAME} PRIVATE 
    ${RAYLIB_LIBRARY_PATH}
    winmm 
    gdi32 
    opengl32 
    user32 
    shell32
)

# Enable Edit & Continue (Hot Reload) for C++ inside Visual Studio CMake
if(MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /ZI")
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /INCREMENTAL")
endif()
