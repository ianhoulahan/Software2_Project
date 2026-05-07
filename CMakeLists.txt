cmake_minimum_required(VERSION 3.14)

# Renamed to match your repository
project(Software2_Project CXX)

# Use modern C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- FETCH RAYLIB MAGIC ---
include(FetchContent)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG        master 
)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(raylib)
# ---------------------------

# Pointing back to the standard 'src' folder
add_executable(Software2_Project
    src/main.cpp
    src/Level.cpp
    src/Obstacle.cpp
)

# Link raylib to your specific project name
target_link_libraries(Software2_Project PRIVATE raylib)

# Tell the compiler to look inside the "src" folder for our .h files
target_include_directories(Software2_Project PRIVATE src)

# 1. Create a standalone task that ALWAYS copies the assets
add_custom_target(CopyAssets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
    ${CMAKE_CURRENT_BINARY_DIR}/assets
)

# 2. Tell Ninja that the game CANNOT launch until CopyAssets is finished
add_dependencies(Software2_Project CopyAssets)