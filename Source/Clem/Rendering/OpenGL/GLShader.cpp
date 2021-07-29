// Copyright 2021 SMS
// License(Apache-2.0)

#include "GLShader.h"
#include <cassert>
#include <glad/glad.h>
#include <type_traits>
#include <vector>

namespace clem
{

static_assert(std::is_same<GLShader::id_type, GLuint>::value);

GLShader::GLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
{
	// Create an empty vertex shader handle
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Send the vertex shader source code to GL
	// Note that std::string's .c_str is NULL character terminated.
	const GLchar* source = (const GLchar*)vertexSrc.c_str();
	glShaderSource(vertexShader, 1, &source, 0);

	// Compile the vertex shader
	glCompileShader(vertexShader);

	GLint isCompiled = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
	if(isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

		glDeleteShader(vertexShader);

		assert(false && "vertex shader compilation failure");
		return;
	}

	// Create an empty fragment shader handle
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Send the fragment shader source code to GL
	// Note that std::string's .c_str is NULL character terminated.
	source = (const GLchar*)fragmentSrc.c_str();
	glShaderSource(fragmentShader, 1, &source, 0);

	// Compile the fragment shader
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
	if(isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

		glDeleteShader(fragmentShader);
		glDeleteShader(vertexShader);

		assert(false && "fragment shader compilation failure");
		return;
	}

	// Vertex and fragment shaders are successfully compiled.
	// Now time to link them together into a program.
	// Get a program object.
	handle = glCreateProgram();

	// Attach our shaders to our program
	glAttachShader(handle, vertexShader);
	glAttachShader(handle, fragmentShader);

	// Link our program
	glLinkProgram(handle);

	// Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(handle, GL_LINK_STATUS, (int*)&isLinked);
	if(isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(handle, maxLength, &maxLength, &infoLog[0]);

		glDeleteProgram(handle);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		assert(false && "shader link failure");
		return;
	}

	// Always detach shaders after a successful link.
	glDetachShader(handle, vertexShader);
	glDetachShader(handle, fragmentShader);
}

GLShader::~GLShader()
{
	glDeleteProgram(handle);
}

void GLShader::bind()
{
	glUseProgram(handle);
}

} // namespace clem