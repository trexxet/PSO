#pragma once

#include "glad.h"
#include <GLFW/glfw3.h>


class Window {

	GLFWwindow* window;

public:
	Window ();
	~Window ();

	void mainLoop ();
};
