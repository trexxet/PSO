#include "Canvas.h"
#include <vector>


void Canvas::initBuffers (Canvas::primBuffers &bufs) {
	glGenVertexArrays (1, &(bufs.VAO));
	glBindVertexArray (bufs.VAO);
	glGenBuffers (1, &(bufs.VBO));
}


void Canvas::loadBuffes (const float dom_x, const float dom_y) {
	loadPlotBuffers ();
	loadAxesBuffers (dom_x, dom_y);
}


void Canvas::loadPlotBuffers () {
	std::vector<GLfloat> vertices = {
			//x   y   s   t
			 -1,  1,  0,  1,
			 -1, -1,  0,  0,
			  1,  1,  1,  1,
			  1,  1,  1,  1,
			 -1, -1,  0,  0,
			  1, -1,  1,  0
	};
	plotBuffers.size = (GLuint) vertices.size ();
	glBindVertexArray (plotBuffers.VAO);
	glBindBuffer (GL_ARRAY_BUFFER, plotBuffers.VBO);
	glBufferData (GL_ARRAY_BUFFER, plotBuffers.size * sizeof (GLfloat), vertices.data (), GL_STATIC_DRAW);
	glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (GLvoid*) 0); // x, y
	glEnableVertexAttribArray (0);
	glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (GLvoid*) (2*sizeof(float))); // s, t
	glEnableVertexAttribArray (1);
}


void Canvas::loadAxesBuffers (const float dom_x, const float dom_y) {
	// Axis lines
	std::vector<GLfloat> vertices = {-(width / 2.f), 0, width / 2.f, 0,
	                                 0, -(height / 2.f), 0, height / 2.f};
	// Notches parameters
	const GLfloat notch_size = 10.f;
	GLfloat step_x = width / dom_x;
	GLfloat step_y = height / dom_y;
	int nnotch_x = (int) (dom_x / 2.f);
	int nnotch_y = (int) (dom_y / 2.f);
	// X-axis notches
	for (int i = -nnotch_x; i <= nnotch_x; i++) {
		vertices.push_back (i * step_x);
		vertices.push_back (-notch_size / 2.f);
		vertices.push_back (i * step_x);
		vertices.push_back (notch_size / 2.f);
	}
	// Y-axis notches
	for (int i = -nnotch_y; i <= nnotch_y; i++) {
		vertices.push_back (-notch_size / 2.f);
		vertices.push_back (i * step_y);
		vertices.push_back (notch_size / 2.f);
		vertices.push_back (i * step_y);
	}

	// Load to OpenGL
	axesBuffers.size = (GLuint) vertices.size ();
	glBindVertexArray (axesBuffers.VAO);
	glBindBuffer (GL_ARRAY_BUFFER, axesBuffers.VBO);
	glBufferData (GL_ARRAY_BUFFER, axesBuffers.size * sizeof (GLfloat), vertices.data (), GL_STATIC_DRAW);
	glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray (0);
}


void Canvas::render (size_t scr_w, size_t scr_h, GLuint plot_texture) {
	glViewport ((GLint) (scr_w - width), (GLint) (scr_h - height), (int) width, (int) height);
	shaderProg.use ();
	shaderProg.setUniform ("canvas_w", (GLint) width);
	shaderProg.setUniform ("canvas_h", (GLint) height);
	renderPlot (plot_texture);
	renderAxes ();
}


void Canvas::renderPlot (GLuint plot_texture) {
	shaderProg.setUniform ("renderMode", 1);
	if (plot_texture != 0) {
		glActiveTexture (GL_TEXTURE0);
		glBindTexture (GL_TEXTURE_2D, plot_texture);
		shaderProg.setUniform ("plotTexture", 0);
	}
	if (plotBuffers.VAO != 0) {
		glBindVertexArray (plotBuffers.VAO);
		glDrawArrays (GL_TRIANGLES, 0, plotBuffers.size / 2);
	}
}


void Canvas::renderAxes () {
	shaderProg.setUniform ("renderMode", 3);
	if (axesBuffers.VAO != 0) {
		glBindVertexArray (axesBuffers.VAO);
		glDrawArrays (GL_LINES, 0, axesBuffers.size / 2);
	}
}
