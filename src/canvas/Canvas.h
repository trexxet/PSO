#pragma once

#include "glad.h"
#include "../gl/Shader.h"

#include <cstddef>

class Canvas {

	ShaderProgram shaderProg;

	void renderPlot ();
	void renderAxes ();

public:
	const size_t width = 600;
	const size_t height = 600;

	void render ();

	Canvas() : shaderProg ("Canvas", Shader::fromFile, "../shaders/shader.vert",
	                       Shader::fromFile, "../shaders/shader.frag") {}
};
