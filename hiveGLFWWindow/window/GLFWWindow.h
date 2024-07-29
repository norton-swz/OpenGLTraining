#pragma once
#include <GLFW/glfw3.h>
#include "../Config/GLFWWindowConfig.h"

void framebuffer_size_callback(GLFWwindow* vWindow, int vWidth, int vHeight);
namespace hiveWindow
{
	class CGLFWWindow
	{
	public:
		CGLFWWindow();
		~CGLFWWindow() = default;
		GLFWwindow* getMyWindow() const { return m_pWindow; }
		const int getWidth() const { return m_Width; }
		const int getHeight() const { return m_Height; }
		bool readFormXML(const CGLFWWindowConfig& vConfig);
		bool initWindow();
		void run();
		void processInput();

	private:
		void __registerEvents() const;
		GLFWwindow* m_pWindow;
		int m_MajorVersion;
		int m_MinorVersion;
		int m_Width;
		int m_Height;
		std::string m_WindowName;
		bool m_UseCoreProfile;
	};
}


