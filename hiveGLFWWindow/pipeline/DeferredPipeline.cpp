#include "DeferredPipeline.h"
#include "../primitive/Primitive.h"


namespace hiveWindow
{
	CDeferredPipeline::CDeferredPipeline(const std::vector<std::string>& vVertShaderPath, const std::vector<std::string>& vFragShaderPath, int vWidth, int vHeight)
		: m_pQuadVAO(CPrimitive::createQuad())
	{
		m_pGeomRenderPass = std::make_shared<CGeometryRenderPass>(vVertShaderPath[0], vFragShaderPath[0]);
		m_pGeomRenderPass->init(vWidth, vHeight);
		m_pShadowRenderPass = std::make_shared<CShadowRenderPass>(vVertShaderPath[1], vFragShaderPath[1]);
		m_pShadowRenderPass->init(vWidth, vHeight);
		m_pLightingRenderPass = std::make_shared<CLightingRenderPass>(m_pShadowRenderPass->getFrameBuffer(), m_pGeomRenderPass->getFrameBuffer(), m_pQuadVAO);
		m_pLightingRenderPass->init(vWidth, vHeight);
	}

	void CDeferredPipeline::render(const std::shared_ptr<CScene>& vScene)
	{
		m_pGeomRenderPass->render(vScene);
		m_pShadowRenderPass->render(vScene);
		m_pLightingRenderPass->render(vScene);
	}

	void CDeferredPipeline::onViewportChange(int vWidth, int vHeight)
	{
		m_pGeomRenderPass->onViewportChange(vWidth, vHeight);
		m_pShadowRenderPass->onViewportChange(vWidth, vHeight);
		m_pLightingRenderPass->onViewportChange(vWidth, vHeight);
	}

	void CDeferredPipeline::setLightingPassMaterial(const std::shared_ptr<CMaterial>& vMaterial)
	{
		m_pLightingRenderPass->setMaterial(vMaterial);
	}
}
