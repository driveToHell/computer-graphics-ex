cmake_minimum_required(VERSION 3.7)
project(Computer_Graphics)

set(SOURCE_FILES
    homeworks_1
    homeworks_2
    nothing
    triangle
    shader
    )

set(SOURCE_School_Homeworks_1 School_Homeworks/1/dda.cpp)
add_executable(homeworks_1 ${SOURCE_School_Homeworks_1})

set(SOURCE_School_Homeworks_2 School_Homeworks/2/fillPolygon.cpp)
add_executable(homeworks_2 ${SOURCE_School_Homeworks_2})

set(SOURCE_Learn_OpenGL_nothing Learn_OpenGL/0_nothing/zeroKara.cpp)
add_executable(nothing ${SOURCE_Learn_OpenGL_nothing})

set(SOURCE_Learn_OpenGL_triangle Learn_OpenGL/1_hi_triangle/hiTriangle.cpp Learn_OpenGL/1_hi_triangle/multiTriangle.cpp)
add_executable(triangle ${SOURCE_Learn_OpenGL_triangle})

set(SOURCE_Learn_OpenGL_shader Learn_OpenGL/2_shader/shader.cpp Learn_OpenGL/2_shader/myShader.h)
add_executable(shader ${SOURCE_Learn_OpenGL_shader})
add_dependencies(shader RES_GLSL)


# use c++11
#set(CMAKE_CXX_STANDARD 11)
# add some flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# OpenGL settings
# glfw3
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework OpenGL")
foreach(item ${SOURCE_FILES})
    target_link_libraries(${item} /usr/local/lib/libglfw.3.2.dylib)
endforeach()

# glew
foreach(item ${SOURCE_FILES})
    target_link_libraries(${item} /usr/local/lib/libGLEW.2.0.0.dylib)
endforeach()

# handle resource files
set(SHADER_DIR Learn_OpenGL/res/shader)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${SHADER_DIR})
file(GLOB SHADER_SOURCES ${CMAKE_SOURCE_DIR}/${SHADER_DIR}/*)
add_custom_target(RES_GLSL)
foreach(glsl ${SHADER_SOURCES})
    add_custom_command(TARGET RES_GLSL PRE_BUILD
                       COMMAND ${CMAKE_COMMAND} -E
                       copy ${glsl} ${CMAKE_CURRENT_BINARY_DIR}/${SHADER_DIR}/
                       VERBATIM
                       )
endforeach()
