cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_CXX_STANDARD 17)
project(OpenGL)

add_executable(OpenGL source/Main.cpp source/Shader.cpp source/Renderer.cpp source/Texture.cpp vendors/stb_image.cpp)
target_compile_options(OpenGL PRIVATE "-fsanitize=address")
target_link_options(OpenGL PRIVATE "-fsanitize=address")

target_link_libraries(OpenGL glfw)
target_link_libraries(OpenGL GLEW)
target_link_libraries(OpenGL GL)
target_link_libraries(OpenGL GLU)