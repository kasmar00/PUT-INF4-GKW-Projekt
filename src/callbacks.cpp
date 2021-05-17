#include "callbacks.h"

#include <stdio.h>

#include "Renderer.h"

int callbacks::last_key = GLFW_KEY_UNKNOWN;
float callbacks::mouseSpeed = 0.010f;
bool callbacks::mouseActive = false;

void callbacks::error_callback(int error, const char* description) {
    fputs(description, stderr);
}

void callbacks::key_callback(GLFWwindow* window, int key, int scancode, int action, int mod) {
    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_ESCAPE:
                if (callbacks::last_key == GLFW_KEY_ESCAPE)
                    glfwSetWindowShouldClose(window, GL_TRUE);
                break;
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
        };
        callbacks::last_key = key;
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

void callbacks::cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    glfwSetCursorPos(window, Renderer::wWidth / 2, Renderer::wHeight / 2);
    if (callbacks::mouseActive) {
        Renderer::speed_rot.y = (Renderer::speed_rot.y + mouseSpeed * (Renderer::wWidth / 2 - xpos)) / 2;    // obrót w prawo-lewo
        Renderer::speed_rot.x = (Renderer::speed_rot.x + mouseSpeed * -(Renderer::wHeight / 2 - ypos)) / 2;  // obrót w górę-dół
    }
}

void callbacks::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        if (action == GLFW_PRESS) {
            callbacks::mouseActive = true;
            Renderer::speed_rot.y = 0;
            Renderer::speed_rot.x = 0;
        } else if (action == GLFW_RELEASE) {
            callbacks::mouseActive = false;
            Renderer::speed_rot.y = 0;
            Renderer::speed_rot.x = 0;
        }
    }
}

void callbacks::window_size(GLFWwindow* window, int width, int height) {
    if (height == 0)
        return;
    Renderer::aspectRatio = (float)width / (float)height;
    Renderer::wWidth = (float)width;
    Renderer::wHeight = (float)height;
    glViewport(0, 0, width, height);
}
