#pragma once
#include <stb_image.h>
#include <string>
#include "opengl_class/TextureBuffer.h"
class Texture
{
public:
	Texture(GLenum _texture_type = GL_TEXTURE_2D);
	~Texture();
	bool load(const std::string & path, const bool image_vertical_flip = true);
	bool loadf(const std::string & path, const bool image_vertical_flip = true); // for hdr image
	GLuint getID() { return buffer.getID(); }
private:
	TextureBuffer buffer;
	std::string type;
};

class Texture2D
	: public TextureBuffer
{
public:
	Texture2D() 
		: TextureBuffer(GL_TEXTURE_2D), Wrap_S(GL_REPEAT), Wrap_T(GL_REPEAT), Filter_Min(GL_LINEAR), Filter_Max(GL_LINEAR)
	{}
	~Texture2D() {};
	void setWrapAndFilter(GLuint wrap_s, GLuint wrap_t, GLuint filter_min, GLuint filter_max);
	void setFormat(GLenum internal_format, GLenum format);
	void init(GLuint width, GLuint height, unsigned char* data);
private:
	GLuint Wrap_S; // Wrapping mode on S axis
	GLuint Wrap_T; // Wrapping mode on T axis
	GLuint Filter_Min; // Filtering mode if texture pixels < screen pixels
	GLuint Filter_Max; // Filtering mode if texture pixels > screen pixels
	GLenum Internal_Format;
	GLenum Format;
};

