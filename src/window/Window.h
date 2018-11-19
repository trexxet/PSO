#pragma once

#include "glad.h"
#include <GLFW/glfw3.h>
#include "nuklear/nuklear_common.h"

#include "../opencl/CLEnviroment.h"
#include "../canvas/Canvas.h"
#include "../function/Function.h"

#include <vector>


#define CANVAS_WIDTH 600
#define CANVAS_HEIGHT 600

class Window {

	GLFWwindow* window;
	nk_context* nk_ctx;

	std::vector<Function> functions;
	Function::NameList funcNameList = nullptr;
	size_t selectedFunction = 0;

	CLEnviroment cl_env;
	Canvas* canvas = nullptr;

	void update ();
	void proceedGUI ();
	void render ();

public:
	Window ();
	~Window ();

	void mainLoop ();
};
