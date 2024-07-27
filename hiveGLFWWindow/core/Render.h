#pragma once
#ifdef MYDLL
#define PORT __declspec(dllexport)
#else
#define PORT __declspec(dllimport)
#endif

#include "../core/RenderPass.h"
#include "../core/VertexBuffer.h"
#include "../window/GLFWWindow.h"

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
		std::shared_ptr<CGLFWWindow> m_pWindow;
		std::shared_ptr<CRenderPass> m_pRenderPass;
	};
}
