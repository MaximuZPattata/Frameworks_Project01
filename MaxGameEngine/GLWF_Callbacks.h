#pragma once

#include "OpenGLCommon.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void mouse_callback(GLFWwindow* window, double xPos, double yPos);

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}


