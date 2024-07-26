#include "VertexBuffer.h"
#include <numeric>

hiveVertexBuffer::CVertexBuffer::CVertexBuffer(const std::vector<float>& vVertices, const std::vector<int>& vArribute, GLenum vUsage, GLenum vMode)
	:m_VAO(0), m_VBO(0), m_EBO(0), m_DrawCallMode(vMode), m_VerticesCount(vVertices.size())
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vVertices.size(), vVertices.data(), vUsage);
	__setAttribute(vArribute);
	glBindVertexArray(0);
}

hiveVertexBuffer::CVertexBuffer::CVertexBuffer(const std::vector<float>& vVertices, const std::vector<unsigned int>& vIndices, const std::vector<int>& vArribute, GLenum vUsage, GLenum vMode)
	:m_VAO(0), m_VBO(0), m_EBO(0), m_DrawCallMode(vMode), m_VerticesCount(vVertices.size())
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vVertices.size(), vVertices.data(), vUsage);
	glBindBuffer(GL_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(unsigned int) * vIndices.size(), vIndices.data(), vUsage);
	__setAttribute(vArribute);
	glBindVertexArray(0);
}

hiveVertexBuffer::CVertexBuffer::~CVertexBuffer()
{
	glBindVertexArray(m_VAO);
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	if(m_EBO != 0)
	{
		glDeleteBuffers(1, &m_EBO);
	}
}

void hiveVertexBuffer::CVertexBuffer::Draw() const
{
	glBindVertexArray(m_VAO);
	if (m_EBO != 0)
	{
		glDrawElements(m_DrawCallMode, m_VerticesCount, GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawArrays(m_DrawCallMode, 0, m_VerticesCount);
	}
}

void hiveVertexBuffer::CVertexBuffer::__setAttribute(const std::vector<int>& vAttribute)
{
	unsigned int TotalCount = std::accumulate(vAttribute.begin(), vAttribute.end(), 0);
	unsigned int Steps = 0;
	for (int i = 0; i < vAttribute.size(); ++i)
	{
		glVertexAttribPointer(i, vAttribute[i], GL_FLOAT, GL_FALSE, TotalCount * sizeof(float), (void*)(Steps * sizeof(float)));
		glEnableVertexAttribArray(i);
		Steps += vAttribute[i];
	}
}

