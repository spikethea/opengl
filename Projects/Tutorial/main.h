#pragma once
#include <iostream>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#define _USE_MATH_DEFINES
#include <cmath>

#include <stack>;
#include <corecrt_math_defines.h>

#include "App.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
