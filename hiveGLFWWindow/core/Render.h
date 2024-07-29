#pragma once
#ifdef MYDLL
#define PORT __declspec(dllexport)
#else
#define PORT __declspec(dllimport)
#endif

#include "../core/RenderPass.h"
#include "../window/GLFWWindow.h"
#include "../camera/PerspectiveCamera.h"
#include "Scene.h"
#include "../camera/PerspCamController.h"
#include "../Config/AlgorithmConfig.h"

namespace hiveWindow
{
	class PORT CRender
	{
	public:
		static CRender& getInstance();
		void startup(const std::string& vWindowConfigFileName, const std::string& vAlgorithmConfigFileName);
		void run();
		void init(int vInitWidth, int vInitHeight);
		void tick();
		void onResize(int vWidth, int vHeight);
		void switchRenderAlgorithm();
		void updateAfterSwitchAlgorithm();
		const std::shared_ptr<CPerspCamController>& getCameraController() const { return m_pCamController; }

	private:
		CRender();
		CRender(const CRender&) = delete;
		CRender& operator=(const CRender&) = delete;
		CGLFWWindowConfig m_WindowConfig;
		CAlgorithmConfig m_AlgorithmConfig;
		std::shared_ptr<CPerspCamController> m_pCamController;
		std::shared_ptr<CGLFWWindow> m_pWindow;
		std::shared_ptr<CRenderPass> m_pRenderPass;
		std::shared_ptr<CScene> m_pScene;
		std::shared_ptr<CPerspectiveCamera> m_pCamera;
		std::shared_ptr<CMaterial> m_pMaterial;
		std::shared_ptr<CNode> m_pNode;
		int m_AlgorithmIndex;
		bool m_Switch = false;
	};
}
