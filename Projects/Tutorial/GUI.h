#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


class GUI {
public:
	float size = 0.05f;
	int iterations = 0;

	void init(GLFWwindow* window);

	void draw();

	void UIrender();

	void cleanup();
};