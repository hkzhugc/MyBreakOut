#pragma once
#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <vector>

struct VertexAttributeConfig
{
	VertexAttributeConfig(GLint _size, GLenum _type, GLboolean _normalized, GLsizei _stride, const void* _pointer)
		: size(_size), type(_type), normalized(_normalized), stride(_stride), pointer(_pointer)
	{}
	VertexAttributeConfig() {}
	GLint size;
	GLenum type;
	GLboolean normalized;
	GLsizei stride;
	const void* pointer;

	template <typename T, GLenum type>
	static std::vector<VertexAttributeConfig> genConfig(std::vector<size_t> sizes)
	{
		std::vector<VertexAttributeConfig> ret;
		ret.reserve(sizes.size());
		size_t sum = 0;
		for (auto s : sizes) sum += s;
		size_t type_size = sizeof(T);
		GLsizei stride = type_size * sum;
		sum = 0;
		for (auto s : sizes)
		{
			VertexAttributeConfig c;
			c.size = s;
			c.type = type;
			c.normalized = GL_FALSE;
			c.stride = stride;
			c.pointer = (void *)(sum * type_size);

			ret.push_back(c);
			sum += s;
		}
		return ret;
	}
};



class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void bind() { glBindVertexArray(VAO_ID); }
	void unbind() { glBindVertexArray(0); }
	void draw();
	void drawInstance(size_t instance_num);

	void initAsQuad(); // init as a quad which fill the clip space
	void initAsCube(); // init as a cube length equal to 2 [-1, 1]
	void initAsSphere(size_t segmentX = 64, size_t segmentY = 64); // init as a sphere whith 1 radius
	void genArrayBuffer(size_t size, void* data, const std::vector<VertexAttributeConfig>& configs);
	void genElementBuffer();

	static VertexArray Quad();
	static VertexArray Cube();
	static VertexArray Sphere(size_t segmentX = 64, size_t segmentY = 64);

	GLuint VAO_ID;
	GLuint VBO_ID;
	GLuint EBO_ID;

	size_t num_vertices;
	size_t num_indices;
};

