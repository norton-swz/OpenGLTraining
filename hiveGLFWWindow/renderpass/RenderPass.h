#pragma once
#include <memory>
#include "../core/Scene.h"

namespace hiveWindow
{
	class CRenderPass
	{
	public:
		virtual void render(const std::shared_ptr<CScene>& vScene) = 0;
		virtual void init(int vWidth, int vHeight) { _setupFrameBuffer(vWidth, vHeight); }
		virtual void onViewportChange(int vWidth, int vHeight) {}
		const std::shared_ptr<CFrameBuffer>& getFrameBuffer() const { return m_pFrameBuffer; }
		void setLastRenderPassFrameBuffer(const std::shared_ptr<CFrameBuffer>& vLastRenderPassFramebuffer) { m_pLastRenderPassFramebuffer = vLastRenderPassFramebuffer; }

	protected:
		virtual void _setupFrameBuffer(int vWidth, int vHeight) {}
		std::shared_ptr<CFrameBuffer> m_pFrameBuffer = nullptr;
		std::shared_ptr<CFrameBuffer> m_pLastRenderPassFramebuffer = nullptr;
	};
}


