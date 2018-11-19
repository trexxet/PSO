#pragma once

#include "glad.h"
#include <GLFW/glfw3.h>
#include "nuklear/nuklear_common.h"

#include "../opencl/CLEnviroment.h"
#include "../function/Function.h"

#include <vector>


class Window {

	GLFWwindow* window;
	nk_context* nk_ctx;

	std::vector<Function> functions;
	Function::NameList funcNameList = nullptr;
	int selectedFunction = 0;

	CLEnviroment cl_env;

	void update ();
	void proceedGUI ();
	void render ();

public:
	Window ();
	~Window ();

	void mainLoop ();
};
