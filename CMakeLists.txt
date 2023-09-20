cmake_minimum_required(VERSION 3.10.0)
project(OpenGL)

add_executable(OpenGL source/Main.cpp source/Shader.cpp source/Renderer.cpp source/Texture.cpp source/Window.cpp source/Application.cpp  source/Entity.cpp source/LinearAlgebra.cpp source/Test.cpp vendors/stb_image.cpp)
# add_executable(OpenGL source/Main.cpp source/LinearAlgebra.cpp source/Test.cpp)
target_compile_options(OpenGL PRIVATE -fsanitize=address)
target_link_options(OpenGL PRIVATE -fsanitize=address)

target_link_libraries(OpenGL glfw)
target_link_libraries(OpenGL GLEW)
target_link_libraries(OpenGL GL)