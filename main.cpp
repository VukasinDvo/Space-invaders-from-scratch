#include <iostream>
#include <cstdio>
#include <GLFW/glfw3.h>
#include "buffer.h"
typedef void(*GLFWerrorfun)(int ,const char *);

GLFWerrorfun glfwSetErrorCallback(GLFWerrorfun cbfun);

void error_callback(int error, const char *description) {
    fprintf(stderr,"Error: %s\n", description);
}
// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {
glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        return -1;
    }
    auto window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
   Buffer buf=buffer_init();

    glfwMakeContextCurrent(window);
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

}