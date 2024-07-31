#pragma once
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace hiveWindow
{
	class CShader
	{
	public:
		enum class EShaderType
		{
			VERTEX = GL_VERTEX_SHADER,
			FRAGMENT = GL_FRAGMENT_SHADER,
		};

		CShader(const std::string& vVertShaderPath, const std::string& vFragShaderPath);
		void use() const;
		void setUniform(const std::string& vName, int vValue) const;
		void setUniform(const std::string& vName, const glm::vec3& vValue) const;
		void setUniform(const std::string& vName, const glm::mat4& vMat) const;

	private:
		GLuint __attachShader(const std::string& vShaderPath, EShaderType vShaderType) const;
		static void __dumpShaderCodeFromFile(const std::string& vShaderPath, EShaderType vShaderType, std::string& voShaderCode);
		static GLuint __compileShader(const std::string& vShaderCode, EShaderType vShaderType);
		static void __checkCompileError(GLuint vID, EShaderType vShaderType);
		static void __checkLinkError(GLuint vID);
		static std::string __getShaderTypeName(EShaderType vShaderType);
		GLuint m_ShaderID;
	};
}


