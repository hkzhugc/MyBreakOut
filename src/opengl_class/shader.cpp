#include "shader.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

Shader::Shader(const char * vertexPath, const char * fragmentPath, const char * geometryPath)
{
	// load and complie shader
	GLuint vs_id, fs_id, gs_id;
	vs_id = load_shader_from_file(vertexPath, GL_VERTEX_SHADER);
	fs_id = load_shader_from_file(fragmentPath, GL_FRAGMENT_SHADER);
	if (geometryPath != nullptr)
		gs_id = load_shader_from_file(geometryPath, GL_GEOMETRY_SHADER);

	// create program
	ID = glCreateProgram();
	glAttachShader(ID, vs_id);
	glAttachShader(ID, fs_id);
	if (geometryPath != nullptr)
		glAttachShader(ID, gs_id);

	// link and check error
	glLinkProgram(ID);
	checkCompileErrors(ID, "PROGRAM");

	// delete shader
	glDeleteShader(vs_id);
	glDeleteShader(fs_id);
	if (geometryPath != nullptr)
		glDeleteShader(gs_id);
}

void Shader::compile(const char * vertexSource, const char * fragmentSource, const char * geometrySource)
{
	// load shader from source string buffer
	GLuint vs_id, fs_id, gs_id;
	vs_id = load_shader_from_source(vertexSource, GL_VERTEX_SHADER);
	fs_id = load_shader_from_source(fragmentSource, GL_FRAGMENT_SHADER);
	if (geometrySource != nullptr)
		gs_id = load_shader_from_source(geometrySource, GL_GEOMETRY_SHADER);
	
	// create program
	ID = glCreateProgram();
	glAttachShader(ID, vs_id);
	glAttachShader(ID, fs_id);
	if (geometrySource != nullptr)
		glAttachShader(ID, gs_id);

	// link and check error
	glLinkProgram(ID);
	checkCompileErrors(ID, "PROGRAM");

	// delete shader
	glDeleteShader(vs_id);
	glDeleteShader(fs_id);
	if (geometrySource != nullptr)
		glDeleteShader(gs_id);
}

void Shader::use()
{
	glUseProgram(ID);
}

GLuint Shader::load_shader_from_file(const char * path, const GLenum shader_type)
{
	string code;
	ifstream file;

	// ensure ifstream objects can throw exceptions:
	file.exceptions(ifstream::failbit | ifstream::badbit);
	// try load shader file into string
	try
	{
		file.open(path);
		stringstream shader_stream;
		shader_stream << file.rdbuf();
		file.close();
		code = shader_stream.str();
	}
	catch (ifstream::failure e)
	{
		cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
	}

	const GLchar* code_cstr = code.c_str();
	GLuint shader_id = glCreateShader(shader_type);
	glShaderSource(shader_id, 1, &code_cstr, nullptr);
	glCompileShader(shader_id);

	string check_error_str;
	switch (shader_type)
	{
	case GL_VERTEX_SHADER:
		check_error_str = "vertex shader";
		break;
	case GL_FRAGMENT_SHADER:
		check_error_str = "fragment shader";
		break;
	case GL_GEOMETRY_SHADER:
		check_error_str = "geometry shader";
		break;
	default:
		break;
	}
	checkCompileErrors(shader_id, check_error_str);
	return shader_id;
}

GLuint Shader::load_shader_from_source(const GLchar * source, const GLenum shader_type)
{
	GLuint shader_id = glCreateShader(shader_type);
	glShaderSource(shader_id, 1, &source, nullptr);
	glCompileShader(shader_id);

	string check_error_str;
	switch (shader_type)
	{
	case GL_VERTEX_SHADER:
		check_error_str = "vertex shader";
		break;
	case GL_FRAGMENT_SHADER:
		check_error_str = "fragment shader";
		break;
	case GL_GEOMETRY_SHADER:
		check_error_str = "geometry shader";
		break;
	default:
		break;
	}
	checkCompileErrors(shader_id, check_error_str);
	return shader_id;
}

// utility function for checking shader compilation/linking errors.
// ------------------------------------------------------------------------
void Shader::checkCompileErrors(GLuint shader, std::string type)
{
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}
