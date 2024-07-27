#include "GLFWWindow.h"
#include <HiveLogger.h>

hiveWindow::CGLFWWindow::CGLFWWindow()
	:m_pWindow(nullptr), m_MajorVersion(3), m_MinorVersion(3), m_Width(0), m_Height(0), m_WindowName("")
{
}

bool hiveWindow::CGLFWWindow::readFormXML(const CGLFWWindowConfig& vConfig)
{
	//TODO 代码过长，考虑进一步抽象
	std::optional<int> Width = vConfig.getAttribute<int>("Width");
	std::optional<int> Height = vConfig.getAttribute<int>("Height");
	std::optional<std::string> WindowName = vConfig.getAttribute<std::string>("WindowName");
	std::optional<int> MajorVersion = vConfig.getAttribute<int>("MajorVersion");
	std::optional<int> MinorVersion = vConfig.getAttribute<int>("MinorVersion");
	std::optional<bool> UseCoreProfile = vConfig.getAttribute<bool>("UseCoreProfile");
	if (Width.has_value() && Height.has_value())
	{
		if (Width.value() > 0 && Height.value() > 0)
		{
			m_Width = Width.value();
			m_Height = Height.value();
		}
		else
		{
			HIVE_LOG_FATAL("Invalid Window Size");
			return false;
		}
	}
	if (WindowName.has_value())
	{
		m_WindowName = WindowName.value();
	}
	else
	{
		HIVE_LOG_FATAL("Invalid Window Name");
		return false;
	}
	if (MajorVersion.has_value())
	{
		if (MajorVersion.value() > 0 && MajorVersion.value() <= 4)
		{
			m_MajorVersion = MajorVersion.value();
		}
		else
		{
			HIVE_LOG_FATAL("Invalid OpenGL Major Version");
			return false;
		}
	}
	if (MinorVersion.has_value())
	{
		if (MinorVersion.value() >= 0 && MinorVersion.value() <= 6)
			m_MinorVersion = MinorVersion.value();
		else
		{
			HIVE_LOG_FATAL("Invalid OpenGL Minor Version");
			return false;
		}
	}
	if (UseCoreProfile.has_value())
		m_UseCoreProfile = UseCoreProfile.value();
	return true;
}

bool hiveWindow::CGLFWWindow::initWindow()
{
	if (!glfwInit())
	{
		HIVE_LOG_FATAL("Failed to initialize GLFW");
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_MajorVersion);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_MinorVersion);
	glfwWindowHint(GLFW_OPENGL_PROFILE, m_UseCoreProfile ? GLFW_OPENGL_CORE_PROFILE : GLFW_OPENGL_COMPAT_PROFILE);

	m_pWindow = glfwCreateWindow(m_Width, m_Height, m_WindowName.c_str(), nullptr, nullptr);
	if (m_pWindow == nullptr)
	{
		HIVE_LOG_FATAL("Failed to create GLFW window");
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(m_pWindow);
	glfwSetFramebufferSizeCallback(m_pWindow, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		HIVE_LOG_FATAL("Failed to initialize GLAD");
		m_pWindow = nullptr;
		glfwTerminate();
		return false;
	}
	return true;
}

void framebuffer_size_callback(GLFWwindow* vWindow, int vWidth, int vHeight)
{
	glViewport(0, 0, vWidth, vHeight);
}