// Copyright 2021 SMS
// License(Apache-2.0)

#include "GLShader.h"
#include "Clem/Assert.h"
#include <cassert>
#include <fstream>
#include <glad/glad.h>
#include <type_traits>
#include <unordered_map>
#include <vector>

namespace fs = std::filesystem;

namespace clem
{

static_assert(std::is_same<GLShader::id_type, GLuint>::value);
static_assert(std::is_same<char, GLchar>::value);

GLShader::GLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
{
	GLint success;

	// 编译顶点着色器
	auto vertexShader = glCreateShader(GL_VERTEX_SHADER);

	const GLchar* source = (const GLchar*)vertexSrc.c_str();

	glShaderSource(vertexShader, 1, &source, 0);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glDeleteShader(vertexShader);
		handleError("vertex shader compilation failure");
		return;
	}

	// 编译片段着色器
	auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	source = (const GLchar*)fragmentSrc.c_str();

	glShaderSource(fragmentShader, 1, &source, 0);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glDeleteShader(fragmentShader);
		glDeleteShader(vertexShader);
		handleError("fragment shader compilation failure");
		return;
	}

	// 创建程序
	handle = glCreateProgram();

	glAttachShader(handle, vertexShader);
	glAttachShader(handle, fragmentShader);

	glLinkProgram(handle);

	glGetProgramiv(handle, GL_LINK_STATUS, (int*)&success);
	if(success == GL_FALSE)
	{
		glDeleteProgram(handle);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		handleError("shader link failure");
		return;
	}

	glDetachShader(handle, vertexShader);
	glDetachShader(handle, fragmentShader);
}

GLShader::GLShader(const fs::path& path)
{
	fs::path cache = "assets/cache/shader/opengl";
	if(!fs::exists(cache))
		fs::create_directories(cache);

	// 读入源代码
	std::string   source;
	std::ifstream file(path, std::ios::binary);
	if(!file.is_open())
		return;
	source.resize(fs::file_size(path));
	file.read(source.data(), source.size());

	// 拆分顶点着色器源代码与片段着色器源代码
	std::string sources[2];

	std::unordered_map<int, std::string> tokens = {
			{0, "#type vertex"},
			{1, "#type fragment"},
			{1, "#type pixel"}};

	size_t begin = 0, currentType;

	size_t           pos = 0, eol;
	std::string_view src(source), line;
	eol = src.find("\r\n", pos);
	do
	{
		line = src.substr(pos, eol - pos);

		for(auto [type, token] : tokens)
		{
			if(line == token)
			{
				if(begin)
				{
					sources[currentType] = source.substr(begin, pos);
					begin                = 0;
				}
				currentType = type;
				begin       = pos + token.size();
			}
		}

		pos = eol + 2;
		eol = src.find("\r\n", pos);
	} while(eol != std::string::npos);

	if(eol == std::string::npos)
		sources[currentType] = source.substr(begin, pos);

	handle = glCreateProgram();

	const auto  name        = path.filename().string();
	const char* extension[] = {".vert", ".freg"};
	GLenum      type[]      = {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};

	for(int i = 0; i < 2; i++)
	{
		fs::path binary = path.parent_path() / (name + extension[i]);
		assert(fs::exists(binary));
		auto size = fs::file_size(binary);

		std::ifstream file(binary, std::ios::binary);
		assert(file.is_open());

		std::vector<std::byte> buffer;
		buffer.resize(size);
		file.read((char*)buffer.data(), size);
		file.close();

		auto shader = glCreateShader(type[i]);
		glShaderBinary(1, &shader, GL_SHADER_BINARY_FORMAT_SPIR_V, buffer.data(), (GLsizei)buffer.size());
		glAttachShader(handle, shader);
	}
}

GLShader::~GLShader()
{
	glDeleteProgram(handle);
}

void GLShader::bind()
{
	glUseProgram(handle);
}

void GLShader::uploadUniform(const std::string& name, const Matrix4& matrix)
{
	auto location = glGetUniformLocation(handle, name.c_str());
	glUniformMatrix4fv(location, 1, false, &matrix.m[0][0]); // TODO: 验证参数 tanspose, value 是否正确性.

	assert(glGetError() == GL_NO_ERROR);
}

void GLShader::handleError(const std::string& msg)
{
	GLint maxLength = 0;
	glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &maxLength);

	std::vector<char> infoLog(maxLength);
	glGetProgramInfoLog(handle, maxLength, &maxLength, infoLog.data());

	Assert::isTrue(false, std::format("{}: {}", msg, std::string(infoLog.data())));
}

} // namespace clem