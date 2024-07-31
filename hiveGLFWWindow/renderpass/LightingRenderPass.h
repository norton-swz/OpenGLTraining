#pragma once
#include "RenderPass.h"

namespace hiveWindow
{
	class CLightingRenderPass : public CRenderPass
	{
	public:
		CLightingRenderPass(const std::shared_ptr<CFrameBuffer>& vFrameBuffer, const std::shared_ptr<CVertexBuffer>& vQuadVAO);
		// ͨ�� CRenderPass �̳�
		void render(const std::shared_ptr<CScene>& vScene) override;
		void setMaterial(const std::shared_ptr<CMaterial>& vMaterial);
	private:
		std::shared_ptr<CFrameBuffer> m_pGeomFrameBuffer;
		std::shared_ptr<CVertexBuffer> m_pQuadVAO;
		std::shared_ptr<CMaterial> m_Material;
	};
}


