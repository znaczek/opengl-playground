project(tetris)
cmake_minimum_required(VERSION 3.16)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${gltext_SOURCE_DIR}/cmake/")

find_package(Freetype REQUIRED)
find_package(Graphite2)

set(HEADERS
        src/common.h
        src/models/model_asset.h
        src/camera.h
        src/models/model.h
        src/models/board.h
        src/shaderprogram.h
        src/game.h
        src/models/figure.h
        src/models/cuboidGenerator.h
        src/models/blocks.h
    gltext/gltext.hpp
)

set(FILES
        src/common.cpp
        src/models/model.cpp
        src/models/board.cpp
        src/camera.cpp
        src/shaderprogram.cpp
        src/game.cpp
        src/models/figure.cpp
        src/models/cuboidGenerator.cpp
        src/models/blocks.cpp
)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/glm)
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/gltext)
add_subdirectory(${PROJECT_SOURCE_DIR}/gltext)
link_directories(${PROJECT_SOURCE_DIR}/gltext)

add_executable(tetris main_file.cpp ${HEADERS} ${FILES})
target_link_libraries(tetris PUBLIC GL glfw GLEW gltext ${FREETYPE_LIBRARY} ${GRAPHITE2_LIBRARY})
#target_link_libraries(tetris PRIVATE gltext)
