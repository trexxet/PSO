#include "Window.h"
#include <cstdio>
#include <stdexcept>


void error_callback (int error, const char* desc) {
	fprintf(stderr, "Error: %s\n", desc);
}


Window::Window () {
	glfwSetErrorCallback (error_callback);
	if (!glfwInit ())
		throw std::runtime_error ("Failed to init GLFW");
	glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
	window = glfwCreateWindow (800, 600, "PSO", nullptr, nullptr);
	if (!window)
		throw std::runtime_error ("Failed to create window");
	glfwMakeContextCurrent (window);
	gladLoadGLLoader ((GLADloadproc) glfwGetProcAddress);
	glfwSwapInterval (1);

}


Window::~Window () {
	if (window)
		glfwDestroyWindow (window);
	glfwTerminate ();
}


void Window::mainLoop () {
	while (!glfwWindowShouldClose (window)) {
		glfwSwapBuffers (window);
		glfwPollEvents ();
	}
}
