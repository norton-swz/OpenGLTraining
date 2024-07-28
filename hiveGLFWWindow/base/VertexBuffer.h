#pragma once
#include "HiveConfig.h"
#include <glad/glad.h>
#include <vector>

namespace hiveWindow
{
	class CVertexBuffer
	{
	public:
		CVertexBuffer(const std::vector<float>& vVertices, const std::vector<int>& vArribute, GLenum vUsage = GL_STATIC_DRAW, GLenum vMode = GL_TRIANGLES);
		CVertexBuffer(const std::vector<float>& vVertices, const std::vector<unsigned int>& vIndices, const std::vector<int>& vArribute, GLenum vUsage = GL_STATIC_DRAW, GLenum vMode = GL_TRIANGLES);
		~CVertexBuffer();
		void Draw() const;
	private:
		unsigned int m_VAO;
		unsigned int m_VBO;
		unsigned int m_EBO;
		GLenum m_DrawCallMode;
		GLsizei m_VerticesCount;
		void __setAttribute(const std::vector<int>& vAttribute);
	};
}