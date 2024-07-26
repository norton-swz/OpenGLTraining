#include "Shader.h"
#include <fstream>
#include <sstream>
#include <HiveLogger.h>

hiveWindow::CShader::CShader(const std::string& vVertShaderPath, const std::string& vFragShaderPath)
{
	m_ShaderID = glCreateProgram();
	GLuint VertID = __attachShader(vVertShaderPath, EShaderType::VERTEX);
	GLuint FragID = __attachShader(vFragShaderPath, EShaderType::FRAGMENT);
	glAttachShader(m_ShaderID, VertID);
	glAttachShader(m_ShaderID, FragID);
	glLinkProgram(m_ShaderID);
	__checkLinkError(m_ShaderID);
	glDeleteShader(VertID);
	glDeleteShader(FragID);
}

void hiveWindow::CShader::use() const
{
	glUseProgram(m_ShaderID);
}

void hiveWindow::CShader::setUniform(const std::string& vName, const glm::vec3& vValue) const
{
	glUniform3f(glGetUniformLocation(m_ShaderID, vName.c_str()), vValue[0], vValue[1], vValue[2]);
}

void hiveWindow::CShader::setUniform(const std::string& vName, const glm::mat4& vMat) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_ShaderID, vName.c_str()), 1, GL_FALSE, &vMat[0][0]);
}

GLuint hiveWindow::CShader::__attachShader(const std::string& vShaderPath, EShaderType vShaderType) const
{
	std::string ShaderCode;
	__dumpShaderCodeFromFile(vShaderPath, vShaderType, ShaderCode);
	return __compileShader(ShaderCode, vShaderType);
}

void hiveWindow::CShader::__dumpShaderCodeFromFile(const std::string& vShaderPath, EShaderType vShaderType, std::string& voShaderCode)
{
	std::ifstream ShaderFile;
	ShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		ShaderFile.open(vShaderPath);
		std::stringstream ShaderStream;
		ShaderStream << ShaderFile.rdbuf();
		ShaderFile.close();
		voShaderCode = ShaderStream.str();
	}
	catch (std::ifstream::failure& Error)
	{
		HIVE_LOG_ERROR("{} shader file READ failed: {}\n{}", __getShaderTypeName(vShaderType), vShaderPath, Error.what());
	}
}

GLuint hiveWindow::CShader::__compileShader(const std::string& vShaderCode, EShaderType vShaderType)
{
	GLuint ShaderID = glCreateShader(static_cast<GLenum>(vShaderType));
	const char* ShaderCodeCStr = vShaderCode.c_str();
	glShaderSource(ShaderID, 1, &ShaderCodeCStr, nullptr);
	glCompileShader(ShaderID);
	__checkCompileError(ShaderID, vShaderType);
	return ShaderID;
}

void hiveWindow::CShader::__checkCompileError(GLuint vID, EShaderType vShaderType)
{
	GLint IsSuccess;
	GLchar InfoLog[1024];
	glGetShaderiv(vID, GL_COMPILE_STATUS, &IsSuccess);
	if (!IsSuccess)
	{
		glGetShaderInfoLog(vID, 1024, nullptr, InfoLog);
		HIVE_LOG_ERROR("shader COMPILE failed: {}\n{}", __getShaderTypeName(vShaderType), InfoLog);
	}
}

void hiveWindow::CShader::__checkLinkError(GLuint vID)
{
	GLint IsSuccess;
	GLchar InfoLog[1024];
	glGetProgramiv(vID, GL_LINK_STATUS, &IsSuccess);
	if (!IsSuccess)
	{
		glGetProgramInfoLog(vID, 1024, nullptr, InfoLog);
		HIVE_LOG_ERROR("shader LINK failed: \n{}", InfoLog);
	}
}

std::string hiveWindow::CShader::__getShaderTypeName(EShaderType vShaderType)
{
	if (vShaderType == EShaderType::VERTEX) return "VERTEX";
	if (vShaderType == EShaderType::FRAGMENT) return "FRAGMENT";
	return "UNDEFINED";
}
