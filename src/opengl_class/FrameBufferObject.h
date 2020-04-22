#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "TextureBuffer.h"
#include "RenderBuffer.h"

class FrameBufferObject
{
public:
	FrameBufferObject();
	~FrameBufferObject();

	GLuint FBO_ID;
	void bind() { glBindFramebuffer(GL_FRAMEBUFFER, FBO_ID); }
	void unbind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }
	void attachTexture(TextureBuffer& tex_buffer, GLenum attachment, GLint mipmap_level = 0);
	void attachRenderBuffer(RenderBuffer& render_buffer, GLenum attachment);
	bool checkValid();
private:
	size_t tex_attachment_count;
};

