#pragma once
#ifdef MYDLL
#define PORT __declspec(dllexport)
#else
#define PORT __declspec(dllimport)
#endif

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Config/GLFWWindowConfig.h"

void framebuffer_size_callback(GLFWwindow* vWindow, int vWidth, int vHeight);
namespace hiveWindow
{
	//TODO  不能将整个类暴露给外部
	class PORT CGLFWWindow
	{
	public:
		CGLFWWindow();
		~CGLFWWindow() = default;
		GLFWwindow* getMyWindow() const { return m_pWindow; }
		const int getWidth() const { return m_Width; }
		const int getHeight() const { return m_Height; }
		bool readFormXML(const CGLFWWindowConfig& vConfig);
		bool initWindow();
	private:
		GLFWwindow* m_pWindow;
		int m_MajorVersion;
		int m_MinorVersion;
		int m_Width;
		int m_Height;
		//int m_XPos;
		//int m_YPos;
		std::string m_WindowName;
		bool m_UseCoreProfile;
	};
}


