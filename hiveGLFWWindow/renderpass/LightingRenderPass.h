#pragma once
#include "RenderPass.h"

namespace hiveWindow
{
	class CLightingRenderPass : public CRenderPass
	{
	public:
		CLightingRenderPass(const std::shared_ptr<CFrameBuffer>& vShadowFrameBuffer, const std::shared_ptr<CFrameBuffer>& vGeomFrameBuffer, const std::shared_ptr<CVertexBuffer>& vQuadVAO);
		// Í¨¹ý CRenderPass ¼Ì³Ð
		void render(const std::shared_ptr<CScene>& vScene) override;
		void setMaterial(const std::shared_ptr<CMaterial>& vMaterial);
	private:
		std::shared_ptr<CFrameBuffer> m_pGeomFrameBuffer;
		std::shared_ptr<CFrameBuffer> m_pShadowFrameBuffer;
		std::shared_ptr<CVertexBuffer> m_pQuadVAO;
		std::shared_ptr<CMaterial> m_Material;
	};
}


