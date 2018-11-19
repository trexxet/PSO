#pragma once

#include "glad.h"

#include <map>
#include <string>
#include <vector>


class Shader {
	GLenum type;
	const static std::map<GLenum, std::string> typeStr;
	std::string name;

public:
	GLuint id;

	enum SourceType {
		fromString, fromFile
	};

	Shader (const std::string& name, GLenum type, Shader::SourceType sourceType, const GLchar *source);
	~Shader ();
};


typedef std::vector<Shader *> ShaderList;


class ShaderProgram {
	std::string name;

	void init (const std::string& name, const ShaderList &shaderList);

public:
	GLuint id;

	void use ();

	void setUniform (const GLchar *name, GLint value);
	void setUniform (const GLchar *name, GLfloat value);

	ShaderProgram (const std::string& name, const ShaderList &shaderList);
	ShaderProgram (const std::string& name, Shader::SourceType vertSourceType, const GLchar *vertSource,
	               Shader::SourceType fragSourceType, const GLchar *fragSource);
	~ShaderProgram ();
};
