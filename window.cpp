//#include <stdlib.h>
#include "utils/framebuffer.h"
#include <math.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

int main(){
    Framebuffer fb = Framebuffer();

    if(fb.Init() == -1){
        perror("Error: en el framebuffer");
        return -1;
    }
    printf("Screen size: %dx%d\n", fb.width, fb.height);
    printf("Bits per pixel: %d\n", fb.bpp);

    if(!glfwInit()){
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(fb.width, fb.height, "/dev/fb1", NULL, NULL);
    
    if(!window){
        return -1;
    }

    glfwMakeContextCurrent(window);

    while(!glfwWindowShouldClose(window)){
        glViewport (0, 0, fb.width, fb.height);
        glMatrixMode (GL_PROJECTION);

        glClearColor(255, 255, 255, 255);
        
        glDrawPixels(fb.width, fb.height, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, fb.fb_memory);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}