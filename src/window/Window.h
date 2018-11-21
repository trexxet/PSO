#pragma once

#include "glad.h"
#include <GLFW/glfw3.h>
#include "nuklear/nuklear_common.h"

#include "../opencl/CLEnviroment.h"
#include "../canvas/Canvas.h"
#include "../function/Function.h"

#include <vector>


class Window {
	size_t width = 800, height = 600;

	GLFWwindow* window;
	nk_context* nk_ctx;

	std::vector<Function> functions;
	Function::NameList funcNameList = nullptr;
	size_t selectedFunction = 0;
	Function& currFunction () { return functions.at (selectedFunction); }

	CLEnviroment cl_env;
	Canvas* canvas = nullptr;

	void changeFunction ();

	void update ();
	void proceedGUI ();
	void render ();

public:
	Window ();
	~Window ();

	void mainLoop ();
};
