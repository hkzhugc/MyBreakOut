#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
class TextureBuffer
{
public:
	TextureBuffer(GLenum _texture_type = GL_TEXTURE_2D);
	~TextureBuffer();
	void setTexture(size_t width, size_t height, GLenum internel_format, GLenum format, const void* data, GLenum data_type = GL_UNSIGNED_BYTE);
	void setTexture(size_t width, size_t height, GLenum internel_format, GLenum format, std::vector<const void*> datas, GLenum data_type = GL_UNSIGNED_BYTE);
	void bindUnit(int location) { glBindTextureUnit(location, ID); }
	GLuint getID() { return ID; }
	GLenum getType() { return texture_type_; }
	size_t getWidth() { return width_; }
	size_t getHeight() { return height_; }
protected:
	void resize(size_t width, size_t height);
	void parameteri(GLenum pname, GLenum param);
	void storage(int level, GLenum internal_format);
	void image2D(int level, GLenum format, GLenum type, const void * data);
	void generateMipmap();
private:
	GLuint ID;
	GLenum texture_type_;
	size_t width_;
	size_t height_;
	void setTexture2D(size_t width, size_t height, GLenum internal_format, GLenum format, const void* data, GLenum data_type = GL_UNSIGNED_BYTE);
	void setTexture2DMultiSample(size_t width, size_t height, GLenum internal_format, GLenum format, const void* data, GLenum data_type = GL_UNSIGNED_BYTE);
};

