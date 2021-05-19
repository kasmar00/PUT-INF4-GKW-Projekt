#ifndef __CALLBACKS_H__
#define __CALLBACKS_H__

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class callbacks {
   private:
    static int last_key;
    static float mouseSpeed;
    static bool mouseActive;
    static bool windowFocus;

   public:
    static void error_callback(int error, const char* description);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mod);
    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    static void window_size(GLFWwindow* window, int width, int height);
    static void focus_callback(GLFWwindow* window, int focused);
};

#endif  // __CALLBACKS_H__