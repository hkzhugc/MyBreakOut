#include "Texture.h"



Texture::Texture(GLenum _texture_type)
	: buffer(_texture_type)
{
}

Texture::~Texture()
{
}

bool Texture::load(const std::string & path, const bool image_vertical_flip)
{
	stbi_set_flip_vertically_on_load(image_vertical_flip);
	int width, height, nrChannels;
	unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	if (!data)
	{
		// raise exception
	}
	else
	{
		GLuint internal_format;
		GLuint format;
		switch (nrChannels)
		{
		case 1:
			internal_format = GL_R8;
			format = GL_RED;
			break;
		case 3:
			internal_format = GL_RGB8;
			format = GL_RGB;
			break;
		case 4:
			internal_format = GL_RGBA8;
			format = GL_RGBA;
			break;
		default:
			internal_format = GL_RGBA8;
			format = GL_RGBA;
			break;
		}
		//buffer.resize(width, height);
		//// parameteri can be pack into default_config
		//buffer.parameteri(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		//buffer.parameteri(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		//buffer.parameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		//buffer.parameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//buffer.storage(1, internal_format);
		//buffer.image2D(0, format, GL_UNSIGNED_BYTE, data);
		//buffer.generateMipmap();
	}
	stbi_image_free(data);
	return data != nullptr;
}

bool Texture::loadf(const std::string & path, const bool image_vertical_flip)
{
	return false;
}

void Texture2D::setWrapAndFilter(GLuint wrap_s, GLuint wrap_t, GLuint filter_min, GLuint filter_max)
{
	Wrap_S = wrap_s;
	Wrap_T = wrap_t;
	Filter_Min = filter_min;
	Filter_Max = filter_max;
}

void Texture2D::setFormat(GLenum internal_format, GLenum format)
{
	Internal_Format = internal_format;
	Format = format;
}

void Texture2D::init(GLuint width, GLuint height, unsigned char * data)
{
	resize(width, height);
	parameteri(GL_TEXTURE_WRAP_S, Wrap_S);
	parameteri(GL_TEXTURE_WRAP_T, Wrap_T);
	parameteri(GL_TEXTURE_MIN_FILTER, Filter_Min);
	parameteri(GL_TEXTURE_MAG_FILTER, Filter_Max);
	storage(1, Internal_Format);
	image2D(0, Format, GL_UNSIGNED_BYTE, data);
	generateMipmap();
}
