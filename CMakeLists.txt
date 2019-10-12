cmake_minimum_required(VERSION 3.14)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add source files
file(GLOB_RECURSE SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/src/*.c
        ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Add header files
file(GLOB_RECURSE HEADER_FILES
        ${CMAKE_SOURCE_DIR}/src/*.h
        ${CMAKE_SOURCE_DIR}/src/*.hpp)

include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/lib)

# Define the executable
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} glfw.3 glew SOIL "-framework OpenGL")
