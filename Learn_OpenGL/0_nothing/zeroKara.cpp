//
// Created by Zacks on 2017/4/22.
// Change Color
//
#include <GLFW/glfw3.h>
#include <fstream>

using namespace std;

const int height = 800;
const int width = 800;

void error_callback(int error, const char* description)
{
    fprintf(stderr, "ERROR: %s", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void change_color()
{
    static int r = 0;
    static int g = 128;
    static int b = 255;
    static int dr = 1;
    static int dg = 1;
    static int db = 1;
    glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
    r += dr;
    g += dg;
    b += db;
    if (r > 255 || r < 0) dr = -dr;
    if (g > 255 || g < 0) dg = -dg;
    if (b > 255 || b < 0) db = -db;
    glClear(GL_COLOR_BUFFER_BIT);
}

int main()
{
    if(!glfwInit()) {throw std::runtime_error("glfwInit failed");}
    // set required opengl version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // core profile 摒弃废弃api
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // macOS
    
    glfwSetErrorCallback(error_callback);
    auto window = glfwCreateWindow(width, height, "Title", NULL, NULL);
    if (!window) {throw std::runtime_error("create window failed");}// window is created correctly
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    
    int width, height;
    glfwSwapInterval(1);
    glViewport(0, 0, width, height);
    
    while(!glfwWindowShouldClose(window))
    {
        change_color();
        glfwSwapBuffers(window);
        glfwPollEvents(); // 检查一下有没有事件，没有就过，有就处理
        //glfwWaitEvents(); // sleep threads, wait to receive 1 event al least and then process all received events. USEFUL for editor program
    }
    glfwTerminate();
    return 0;
}