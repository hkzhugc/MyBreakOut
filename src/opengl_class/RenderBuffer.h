#pragma once
#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
class RenderBuffer
{
public:
	RenderBuffer();
	~RenderBuffer();

	void bind() { glBindRenderbuffer(GL_RENDERBUFFER, RBO_ID); }
	void unbind() { glBindRenderbuffer(GL_RENDERBUFFER, 0); }
	void setStorage(size_t width, size_t height, GLenum internal_format);
	GLuint RBO_ID;
};

