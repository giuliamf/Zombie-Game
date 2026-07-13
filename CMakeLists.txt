cmake_minimum_required(VERSION 3.15)
project(ZombieGame VERSION 1.0 LANGUAGES CXX)

# Set C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Find SDL2 and its extensions
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Source files
set(SOURCES
    src/GameData.cpp
    src/Resources.cpp
    src/Text.cpp
    src/State.cpp
    src/EndState.cpp
    src/TitleState.cpp
    src/StageState.cpp
    src/Game.cpp
    src/GameObject.cpp
    src/Component.cpp
    src/Sprite.cpp
    src/SpriteRenderer.cpp
    src/Animation.cpp
    src/Animator.cpp
    src/Camera.cpp
    src/Character.cpp
    src/Collider.cpp
    src/Collision.cpp
    src/PlayerController.cpp
    src/TileMap.cpp
    src/TileSet.cpp
    src/Timer.cpp
    src/Vec2.cpp
    src/Rect.cpp
    src/Music.cpp
    src/InputManager.cpp
    src/Bullet.cpp
    src/Gun.cpp
    src/Zombie.cpp
    src/AIController.cpp
    src/WaveSpawner.cpp
    src/main.cpp
)

# Create executable
add_executable(ZombieGame ${SOURCES})

# Include directories
target_include_directories(ZombieGame PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${SDL2_INCLUDE_DIRS}
)

# Link libraries
target_link_libraries(ZombieGame PRIVATE
    SDL2::SDL2main
    SDL2::SDL2
    SDL2_image::SDL2_image
    SDL2_mixer::SDL2_mixer
    SDL2_ttf::SDL2_ttf
)

# Windows-specific settings
if(WIN32)
    # Hide console window in release builds
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        set_target_properties(ZombieGame PROPERTIES
            WIN32_EXECUTABLE TRUE
        )
    endif()
    
    # Copy SDL2 DLLs to output directory
    if(SDL2_RUNTIME_LIBRARY)
        add_custom_command(TARGET ZombieGame POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${SDL2_RUNTIME_LIBRARY}
            $<TARGET_FILE_DIR:ZombieGame>
        )
    endif()
endif()

# Copy Resources folder to build directory
add_custom_command(TARGET ZombieGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Resources
    $<TARGET_FILE_DIR:ZombieGame>/Resources
)

# Installation rules
install(TARGETS ZombieGame DESTINATION bin)
install(DIRECTORY Resources DESTINATION bin)