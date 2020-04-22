#include "FrameBufferObject.h"



FrameBufferObject::FrameBufferObject()
	: tex_attachment_count(0)
{
	glGenFramebuffers(1, &FBO_ID);
}


FrameBufferObject::~FrameBufferObject()
{
	glDeleteFramebuffers(1, &FBO_ID);
}

void FrameBufferObject::attachTexture(TextureBuffer & tex_buffer, GLenum attachment, GLint mipmap_level)
{
	bind();
	/*if (tex_buffer.texture_type == GL_TEXTURE_CUBE_MAP)
		glFramebufferTexture(GL_FRAMEBUFFER, attachment, tex_buffer.TEX_ID, mipmap_level);
	else if (tex_buffer.TEX_ID)
		glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, tex_buffer.texture_type, tex_buffer.TEX_ID, mipmap_level);*/
	unbind();
}

void FrameBufferObject::attachRenderBuffer(RenderBuffer & render_buffer, GLenum attachment)
{
	bind();
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, render_buffer.RBO_ID);
	unbind();
}

bool FrameBufferObject::checkValid()
{
	bind();
	bool flag = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
	unbind();
	return flag;
}
