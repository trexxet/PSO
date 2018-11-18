#pragma once

#include "glad.h"
#include <GLFW/glfw3.h>
#include "nuklear/nuklear_common.h"


class Window {

	GLFWwindow* window;
	nk_context* nk_ctx;

	void update ();
	void proceedGUI ();
	void render ();

public:
	Window ();
	~Window ();

	void mainLoop ();
};
