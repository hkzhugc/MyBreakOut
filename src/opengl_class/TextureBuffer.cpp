#include "TextureBuffer.h"

TextureBuffer::TextureBuffer(GLenum _texture_type)
	: texture_type_(_texture_type), width_(0), height_(0) // empty some type texture
{
	glCreateTextures(_texture_type, 1, &ID);
}

TextureBuffer::~TextureBuffer()
{
	glDeleteTextures(1, &ID);
}

void TextureBuffer::resize(size_t width, size_t height)
{
	width_ = width;
	height_ = height;
}

void TextureBuffer::parameteri(GLenum pname, GLenum param)
{
	glTextureParameteri(ID, pname, param);
}

void TextureBuffer::storage(int level, GLenum internal_format)
{
	assert(width_ && height_);
	glTextureStorage2D(ID, 1, internal_format, width_, height_);
}

void TextureBuffer::image2D(int level, GLenum format, GLenum type, const void * data)
{
	assert(width_ && height_);
	glTextureSubImage2D(ID, 0, 0, 0, width_, height_, format, type, data);
}

void TextureBuffer::generateMipmap()
{
	glGenerateTextureMipmap(ID);
}

void TextureBuffer::setTexture(size_t width, size_t height, GLenum internal_format, GLenum format, const void * data, GLenum data_type)
{
	switch (texture_type_)
	{
	case GL_TEXTURE_2D:
		setTexture2D(width, height, internal_format, format, data, data_type);
		break;
	case GL_TEXTURE_2D_MULTISAMPLE:
		setTexture2DMultiSample(width, height, internal_format, format, data, data_type);
		break;
	default:
		break;
	}

	// clamp to edge ignore kernel sample failed
	glTexParameteri(texture_type_, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(texture_type_, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// naive linear filtering
	glTexParameteri(texture_type_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(texture_type_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

// for cube map
void TextureBuffer::setTexture(size_t width, size_t height, GLenum internel_format, GLenum format, std::vector<const void*> datas, GLenum data_type)
{
	assert(texture_type_ == GL_TEXTURE_CUBE_MAP);
	assert(datas.size() == 6);
	for (GLuint i = 0; i < 6; ++i)
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, internel_format,
			width, height, 0, format, data_type, datas[i]);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void TextureBuffer::setTexture2D(size_t width, size_t height, GLenum internal_format, GLenum format, const void * data, GLenum data_type)
{
	glTexImage2D(texture_type_, 0, internal_format, width, height, 0, format, data_type, data);
}

void TextureBuffer::setTexture2DMultiSample(size_t width, size_t height, GLenum internal_format, GLenum format, const void * data, GLenum data_type)
{
	glTexImage2DMultisample(texture_type_, 4, internal_format, width, height, GL_TRUE);
}
