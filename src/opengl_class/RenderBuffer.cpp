#include "RenderBuffer.h"



RenderBuffer::RenderBuffer()
{
	glGenRenderbuffers(1, &RBO_ID);
}


RenderBuffer::~RenderBuffer()
{
	glDeleteRenderbuffers(1, &RBO_ID);
}

void RenderBuffer::setStorage(size_t width, size_t height, GLenum internal_format)
{
	bind();
	glRenderbufferStorage(GL_RENDERBUFFER, internal_format, width, height);
	unbind();
}
