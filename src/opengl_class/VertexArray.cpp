#include "VertexArray.h"
using namespace std;
static float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
						 // positions   // texCoords
	-1.0f,  1.0f,  0.0f, 1.0f,
	-1.0f, -1.0f,  0.0f, 0.0f,
	1.0f, -1.0f,  1.0f, 0.0f,

	-1.0f,  1.0f,  0.0f, 1.0f,
	1.0f, -1.0f,  1.0f, 0.0f,
	1.0f,  1.0f,  1.0f, 1.0f
};

static float cubeVertices[] = {
	// back face
	-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
	1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
	1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
	1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
	-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
	-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
	// front face
	-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
	1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
	1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
	1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
	-1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
	-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
	// left face
	-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
	-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
	-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
	-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
	-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
	-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
	// right face
	1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
	1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
	1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
	1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
	1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
	1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
	// bottom face
	-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
	1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
	1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
	1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
	-1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
	-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
	// top face
	-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
	1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
	1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
	1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
	-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
	-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left        
};


VertexArray::VertexArray()
{
	glCreateVertexArrays(1, &VAO_ID);
	VBO_ID = 0;
	EBO_ID = 0;
	num_indices = 0;
	num_vertices = 0;
}


VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &VAO_ID);
}

void VertexArray::draw()
{
	bind();
	if (VBO_ID && !EBO_ID) // only have vertex buffer
	{
		glDrawArrays(GL_TRIANGLES, 0, num_vertices);
	}
	else if (VBO_ID && EBO_ID)
	{
		glDrawElements(GL_TRIANGLE_STRIP, num_indices, GL_UNSIGNED_INT, (void *)0);
	}
	unbind();
}

void VertexArray::drawInstance(size_t instance_num)
{
	bind();
	if (VBO_ID && !EBO_ID) // only have vertex buffer
	{
		glDrawArraysInstanced(GL_TRIANGLES, 0, num_vertices, instance_num);
	}
	else if (VBO_ID && EBO_ID)
	{
		glDrawElementsInstanced(GL_TRIANGLES, num_indices, GL_INT, (void *)0, instance_num);
	}
	unbind();
}

void VertexArray::initAsQuad()
{
	if (EBO_ID || VBO_ID)
		return;
	genArrayBuffer(
		sizeof(quadVertices),
		quadVertices,
		VertexAttributeConfig::genConfig<float, GL_FLOAT>({2, 2})
	);
}

void VertexArray::initAsCube()
{
	if (EBO_ID || VBO_ID)
		return;
	genArrayBuffer(
		sizeof(cubeVertices),
		cubeVertices,
		VertexAttributeConfig::genConfig<float, GL_FLOAT>({ 3, 3, 2 })
	);
}

void VertexArray::initAsSphere(size_t segmentX, size_t segmentY)
{
	if (EBO_ID || VBO_ID)
		return;
	vector<glm::vec3> positions;
	vector<glm::vec3> normals;
	vector<glm::vec2> uvs;
	vector<size_t> indices;
	const float PI = 3.14159265359;
	// calculate pos and uv
	for (size_t i = 0; i <= segmentY; i++)
	{
		for (size_t j = 0; j <= segmentX; j++)
		{
			float x = (float)j / (float)segmentX;
			float y = (float)i / (float)segmentY;

			float theta = y * PI;
			float phi = x * 2 * PI;

			glm::vec3 pos;
			pos.x = cos(phi) * sin(theta);
			pos.y = cos(theta);
			pos.z = sin(phi) * sin(theta);

			positions.push_back(pos);
			normals.push_back(pos);
			uvs.push_back(glm::vec2(x, y));
		}
	}
	// calculate indices
	for (size_t y = 0; y < segmentY; y++)
	{
		if (y % 2 == 0)
		{
			for (int x = 0; x <= segmentX; x++)
			{
				indices.push_back( y      * (segmentX + 1) + x);
				indices.push_back((y + 1) * (segmentX + 1) + x);
			}
		}
		else
		{
			for (int x = segmentX; x >= 0; x--)
			{
				indices.push_back((y + 1) * (segmentX + 1) + x);
				indices.push_back(y      * (segmentX + 1) + x);
			}
		}
	}
	num_vertices = positions.size();
	num_indices = indices.size();

	size_t position_size, normal_size, uv_size, index_size;
	position_size = positions.size() * sizeof(glm::vec3);
	normal_size   = normals.size() * sizeof(glm::vec3);
	uv_size       = uvs.size() * sizeof(glm::vec2);
	index_size    = indices.size() * sizeof(size_t);

	bind();
	glGenBuffers(1, &VBO_ID);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_ID);
	glBufferData(GL_ARRAY_BUFFER, position_size + normal_size + uv_size, nullptr, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, position_size, positions.data());
	glBufferSubData(GL_ARRAY_BUFFER, position_size, normal_size, normals.data());
	glBufferSubData(GL_ARRAY_BUFFER, position_size + normal_size, uv_size, uvs.data());

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void *)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void *)position_size);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void *)(position_size + normal_size));

	glGenBuffers(1, &EBO_ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_size, indices.data(), GL_STATIC_DRAW);

	unbind();
}

void VertexArray::genArrayBuffer(size_t size, void* data, const std::vector<VertexAttributeConfig>& configs)
{
	assert(configs.size());
	glCreateBuffers(1, &VBO_ID);
	glNamedBufferStorage(VBO_ID, size, data, GL_DYNAMIC_STORAGE_BIT);
	glVertexArrayVertexBuffer(VAO_ID, 0, VBO_ID, 0, configs[0].stride);
	for (int i = 0; i < configs.size(); i++)
	{
		auto& config = configs[i];
		glEnableVertexArrayAttrib(VAO_ID, i);
		glVertexArrayAttribFormat(VAO_ID, i, config.size, config.type, config.normalized, (size_t)(config.pointer));
		glVertexArrayAttribBinding(VAO_ID, i, 0);
	}
	if (configs.size())
		num_vertices = size / configs[0].stride;
}

void VertexArray::genElementBuffer()
{
	// TODO :
	glCreateBuffers(1, &EBO_ID);
}
