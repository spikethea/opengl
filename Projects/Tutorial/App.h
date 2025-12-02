#pragma once

#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <stack>
#include <corecrt_math_defines.h>


#include "LSystemMesh.h";


class App {
public:
    std::vector<LSystemMesh> trees;
    int activeIndex = 0;

    void init(GLFWwindow* window);


    void onKey(int key, int scancode, int action, int mods);

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    void selectActiveLSystem(int index);

    void updateActiveLSystem(string Lsystem, float unitLength, float angleDeg);

    void drawCurrentMesh();
};