#include "App.h"



    void App::init (GLFWwindow* window) {
        glfwSetWindowUserPointer(window, this);

        // Set the key callback to our static wrapper
        glfwSetKeyCallback(window, keyCallback);
        //gui.init(window);
    }

    void App::release () {
        gui.cleanup();
        for (int i = 0; i < trees.size(); i++) {
            trees[i].release();
        }
	}


    void App::onKey(int key, int scancode, int action, int mods) {
        if (action == GLFW_PRESS) {
            // Switch L-System
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

            //Adjust Iterations
            if (key == GLFW_KEY_W || key == GLFW_KEY_UP) {
                // Rebuild the active tree
                if (trees[activeIndex].lSystem.iterations < 7) {
					trees[activeIndex].lSystem.iterations++;
                    trees[activeIndex].updateLSystem();
                }
            }

            //Adjust Iterations
            if (key == GLFW_KEY_S || key == GLFW_KEY_DOWN) {
                // Rebuild the active tree
                if (trees[activeIndex].lSystem.iterations > 0) {
                    trees[activeIndex].lSystem.iterations--;
                    trees[activeIndex].updateLSystem();
                }
            }

            //

            
        }

        selectActiveLSystem(activeIndex);
    }

    void App::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        // Get the instance from the user pointer
        App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
        if (app) {
            app->onKey(key, scancode, action, mods);
        }
    }

    void App::selectActiveLSystem(int index) {
        //trees[index].update
    }

    void App::updateActiveLSystem(string Lsystem, float unitLength, float angleDeg) {
        trees[activeIndex].updateLSystem();
    }

    void App::render() {
        drawCurrentMesh();
        //gui.draw();
	}



    void App::drawCurrentMesh() {
        // cout << activeIndex << endl;
        trees[activeIndex].DrawMesh();
    }
