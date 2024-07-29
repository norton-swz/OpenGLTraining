#pragma once
#include <memory>
#include <string>
#include "../base/VertexBuffer.h"
#include "../window/GLFWWindow.h"
#include "../material/Material.h"
#include "../base/FrameBuffer.h"

namespace hiveWindow
{
	class CRenderPass
	{
	public:
		CRenderPass();
		~CRenderPass();

		bool init(const std::string& vAlgorithmConfigFileName);
		void render(const std::shared_ptr<hiveWindow::CGLFWWindow>& vWindow, const std::shared_ptr<CScene>& vScene);
		const std::shared_ptr<CFrameBuffer>& getFrameBuffer() const { return m_pFrameBuffer; }
		//void onViewportChange(int vWidth, int vHeight);
	private:
		std::shared_ptr<CMaterial> m_pMaterial;
		std::shared_ptr<CFrameBuffer> m_pFrameBuffer;
		std::shared_ptr<CVertexBuffer> m_pVertexBuffer;
		
	};
}
