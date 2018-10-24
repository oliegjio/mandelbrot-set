cmake_minimum_required(VERSION 3.12)

set(MY_NAME "mandelbrot_set")
project(${MY_NAME})

set(MY_FILES
    "main.cpp"
)

add_executable("mandelbrot_set" ${MY_FILES})

if (UNIX)
    target_link_libraries(${MY_NAME} "GL" "GLU" "glut")
endif (UNIX)