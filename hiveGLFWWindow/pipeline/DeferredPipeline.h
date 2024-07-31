#pragma once

#include "../pipeline/Pipeline.h"
#include "../base/VertexBuffer.h"
#include "../renderpass/GeometryRenderPass.h"
#include "../renderpass/LightingRenderPass.h"

namespace hiveWindow
{
	class CDeferredPipeline : public CPipeline
	{
	public:
		CDeferredPipeline(const std::string& vVertShaderPath, const std::string& vFragShaderPath, int vWidth, int vHeight);
		// Inherited via CPipeline
		void render(const std::shared_ptr<CScene>& vScene) override;
		void onViewportChange(int vWidth, int vHeight) override;
		void setLightingPassMaterial(const std::shared_ptr<CMaterial>& vMaterial);
	private:
		std::shared_ptr<CVertexBuffer> m_pQuadVAO;
		std::shared_ptr<CGeometryRenderPass> m_pGeomRenderPass;
		std::shared_ptr<CLightingRenderPass> m_pLightingRenderPass;
	};
}