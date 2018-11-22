#pragma once

#include "glad.h"
#include "../gl/Shader.h"

#include <cstddef>

class Canvas {

	ShaderProgram shaderProg;

	typedef struct {
		GLuint VAO, VBO, size;
	} primBuffers;
	primBuffers plotBuffers = {0}, axesBuffers = {0};

	void initBuffers (primBuffers& bufs);
	void loadPlotBuffers ();
	void loadAxesBuffers (const float dom_x, const float dom_y);

	void renderPlot (GLuint plot_texture);
	void renderAxes ();

public:
	const size_t width = 600;
	const size_t height = 600;

	float max_val = 1.f;

	void loadBuffes (const float dom_x, const float dom_y);
	void render (size_t scr_w, size_t scr_h, GLuint plot_texture);

	Canvas() : shaderProg ("Canvas", Shader::fromFile, "../shaders/shader.vert",
	                       Shader::fromFile, "../shaders/shader.frag") {
		initBuffers (plotBuffers);
		initBuffers (axesBuffers);
	}
};
