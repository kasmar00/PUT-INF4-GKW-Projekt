#ifndef __CALLBACKS_H__
#define __CALLBACKS_H__

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class callbacks {
   private:
    /* data */
   public:
    static void error_callback(int error, const char* description);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mod);
    static void window_size(GLFWwindow* window, int width, int height);
};

#endif  // __CALLBACKS_H__