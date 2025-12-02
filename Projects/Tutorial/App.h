#pragma once

#include <iostream>

#include <GLFW/glfw3.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <stack>
#include <corecrt_math_defines.h>

#include "main.h"



#include "LSystemMesh.h";


class App {
public:
    std::vector<LSystemMesh> trees;
    int activeIndex = 0;

    void init(GLFWwindow* window) {
        glfwSetWindowUserPointer(window, this);

        // Set the key callback to our static wrapper
        glfwSetKeyCallback(window, keyCallback);
    }


    void onKey(int key, int scancode, int action, int mods) {
        if (action == GLFW_PRESS) {
            if (key == GLFW_KEY_A || key == GLFW_KEY_LEFT) {
                // Rebuild the active tree
                if (activeIndex > 0) {
                    activeIndex--;
                }
            }

            if (key == GLFW_KEY_D || key == GLFW_KEY_RIGHT) {
                // Rebuild the active tree
                if (activeIndex < trees.size() - 1) {
                    activeIndex++;
                }
            }
        }

        selectActiveLSystem(activeIndex);
    }

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        // Get the instance from the user pointer
        App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
        if (app) {
            app->onKey(key, scancode, action, mods);
        }
    }

    void selectActiveLSystem(int index) {
        //trees[index].update
    }

    void updateActiveLSystem(string Lsystem, float unitLength, float angleDeg) {
        trees[activeIndex].updateLSystem(Lsystem, unitLength, angleDeg);
    }

    void drawCurrentMesh() {
        cout << activeIndex << endl;
        trees[activeIndex].DrawMesh();
    }
};