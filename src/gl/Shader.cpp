#include "Shader.h"
#include "../auxiliary/aux.h"
#include <iostream>
#include <stdexcept>


const std::map<GLenum, std::string> Shader::typeStr = {
		{GL_VERTEX_SHADER,   "Vertex"},
		{GL_FRAGMENT_SHADER, "Fragment"}
};


Shader::Shader (const std::string& name, GLenum type, Shader::SourceType sourceType, const GLchar *source) {
	GLint success = 0;
	std::string log;

	this->name = name;
	this->type = type;

	// Load shader
	id = glCreateShader (type);
	if (sourceType == fromString) {
		glShaderSource (id, 1, &source, nullptr);
		glCompileShader (id);
	} else {
		auto[loaded, loadSuccess] = aux::loadFileToString (std::string(source));
		if (!loadSuccess) {
			throw std::runtime_error (typeStr.at(type) + " shader \"" + name + "\" error: failed to open "
			                          + std::string(source) + " file");
		}
		const GLchar *loadedStr = loaded.c_str ();
		glShaderSource (id, 1, &loadedStr, nullptr);
		glCompileShader (id);
	}

	// Check compile status
	glGetShaderiv (id, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLint logSize = 0;
		glGetShaderiv (id, GL_INFO_LOG_LENGTH, &logSize);
		log.resize ((size_t) logSize);
		glGetShaderInfoLog (id, logSize, nullptr, &log[0]);
		throw std::runtime_error (typeStr.at(type) + " shader \"" + name + "\" error: " + log);
	} else {
		std::cout << typeStr.at(type) << " shader \"" << name << "\" compiled" << std::endl;
	}
}


Shader::~Shader () {
	glDeleteShader (id);
}


void ShaderProgram::init (const std::string& name, const ShaderList &shaderList) {
	GLint success = 0;
	std::string log;

	this->name = name;

	// Link program
	id = glCreateProgram ();
	for (auto shader : shaderList)
		glAttachShader (id, shader->id);
	glLinkProgram (id);

	// Check link status
	glGetProgramiv (id, GL_LINK_STATUS, &success);
	if (!success) {
		GLint logSize = 0;
		glGetProgramiv (id, GL_INFO_LOG_LENGTH, &logSize);
		log.resize ((size_t) logSize);
		glGetProgramInfoLog (id, logSize, nullptr, &log[0]);
		throw std::runtime_error ("Shader program \"" + name + "\" error: " + log);
	} else {
		std::cout << "Shader program \"" << name << "\" linked" << std::endl;
	}
}


ShaderProgram::ShaderProgram (const std::string& name, const ShaderList &shaderList) {
	init (name, shaderList);
}


ShaderProgram::ShaderProgram (const std::string& name, Shader::SourceType vertSourceType, const GLchar *vertSource,
                              Shader::SourceType fragSourceType, const GLchar *fragSource) {
	Shader vertShader (name, GL_VERTEX_SHADER, vertSourceType, vertSource);
	Shader fragShader (name, GL_FRAGMENT_SHADER, fragSourceType, fragSource);
	init (name, {&vertShader, &fragShader});
}


ShaderProgram::~ShaderProgram () {
	glDeleteProgram (id);
}


void ShaderProgram::use () {
	glUseProgram (id);
}


void ShaderProgram::setUniform (const GLchar *name, GLint value) {
	GLint loc = glGetUniformLocation (id, name);
	glUniform1i (loc, value);
}


void ShaderProgram::setUniform (const GLchar *name, GLfloat value) {
	GLint loc = glGetUniformLocation (id, name);
	glUniform1f (loc, value);
}
