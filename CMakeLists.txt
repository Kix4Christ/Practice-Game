cmake_minimum_required(VERSION 3.28)
project(practiceGame LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(snakeTest src/main.cpp "src/Scene.cpp" "src/Game.cpp"
    "src/headers/Game.h" "src/headers/Scene.h" "src/snake.cpp" "src/headers/snake.h" 
    "src/TextScene.cpp" "src/headers/TextScene.h" "src/headers/PlayScene.h" 
    "src/headers/Playfield.h" "src/PlayScene.cpp" "src/headers/Direction.h" "src/Playfield.cpp")
target_link_libraries(snakeTest PRIVATE SFML::Graphics)



add_custom_command(
        TARGET snakeTest POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/resources 
                ${CMAKE_CURRENT_BINARY_DIR}/bin
)