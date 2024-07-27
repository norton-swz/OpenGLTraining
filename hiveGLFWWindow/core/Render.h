#pragma once
#ifdef MYDLL
#define PORT __declspec(dllexport)
#else
#define PORT __declspec(dllimport)
#endif

#include "../Config/AlgorithmConfig.h"
#include "Shader.h"
#include "../window/GLFWWindow.h"
#include "../core/VertexBuffer.h"

namespace hiveWindow
{
	class PORT CRender
	{
	public:
		static CRender& getInstance();
		void startup(const std::string& vWindowConfigFileName, const std::string& vAlgorithmConfigFileName);
		void run();

		void processInput(GLFWwindow* window);

	private:
		CRender();
		CRender(const CRender&) = delete;
		CRender& operator=(const CRender&) = delete;
		CGLFWWindowConfig m_WindowConfig;
		CAlgorithmConfig m_AlgorithmConfig;
		std::shared_ptr<CShader> m_pShader;
		std::shared_ptr<hiveWindow::CGLFWWindow> m_pWindow;
		std::shared_ptr<hiveVertexBuffer::CVertexBuffer> m_pVertexBuffer;
	};
}