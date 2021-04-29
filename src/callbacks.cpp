#include "callbacks.h"

#include <stdio.h>

#include "Renderer.h"

void callbacks::error_callback(int error, const char* description) {
    fputs(description, stderr);
}

void callbacks::key_callback(GLFWwindow* window, int key, int scancode, int action, int mod) {
    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_W:
                Renderer::speed.z = 1;  //do przodu
                break;
            case GLFW_KEY_S:
                Renderer::speed.z = -1;  //do tyłu
                break;
            case GLFW_KEY_A:
                Renderer::speed.x = 1;  //w lewo
                break;
            case GLFW_KEY_D:
                Renderer::speed.x = -1;  //w prawo
                break;
            case GLFW_KEY_SPACE:
                Renderer::speed.y = 1;  // w górę
                break;
            case GLFW_KEY_LEFT_SHIFT:
                Renderer::speed.y = -1;  // w dół
                break;
            case GLFW_KEY_LEFT:
                Renderer::speed_rot.y = 1;  // obrót w lewo
                break;
            case GLFW_KEY_RIGHT:
                Renderer::speed_rot.y = -1;  // obrót w prawo
                break;
            case GLFW_KEY_UP:
                Renderer::speed_rot.x = -1;  // obrót w górę
                break;
            case GLFW_KEY_DOWN:
                Renderer::speed_rot.x = 1;  // obrót w dół
                break;
            default:
                break;
        }
    } else if (action == GLFW_RELEASE) {
        switch (key) {
            case GLFW_KEY_W:
            case GLFW_KEY_S:
                Renderer::speed.z = 0;  //do przodu-tyłu
                break;
            case GLFW_KEY_A:
            case GLFW_KEY_D:
                Renderer::speed.x = 0;  //w lewo-prawo
                break;
            case GLFW_KEY_SPACE:
            case GLFW_KEY_LEFT_SHIFT:
                Renderer::speed.y = 0;  // w górę-dół
                break;

            case GLFW_KEY_LEFT:
            case GLFW_KEY_RIGHT:
                Renderer::speed_rot.y = 0;  // obrót w prawo-lewo
                break;
            case GLFW_KEY_UP:
            case GLFW_KEY_DOWN:
                Renderer::speed_rot.x = 0;  // obrót w górę-dół
                break;
            default:
                break;
        }
    }
}
