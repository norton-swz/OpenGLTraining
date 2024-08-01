#include "LightingRenderPass.h"
#include "../utils/safe.h"

namespace hiveWindow
{
	CLightingRenderPass::CLightingRenderPass(const std::shared_ptr<CFrameBuffer>& vShadowFrameBuffer, const std::shared_ptr<CFrameBuffer>& vGeomFrameBuffer, const std::shared_ptr<CVertexBuffer>& vQuadVAO)
		: m_pQuadVAO(vQuadVAO), m_pGeomFrameBuffer(vGeomFrameBuffer), m_pShadowFrameBuffer(vShadowFrameBuffer){}

	void CLightingRenderPass::render(const std::shared_ptr<CScene>& vScene)
	{
		vScene->getCamera()->getFrameBuffer()->bind();
		glm::vec4 SolidColor = vScene->getCamera()->getSolidColor();
		GL_SAFE_CALL(glClearColor(SolidColor.x, SolidColor.y, SolidColor.z, SolidColor.w));
		GL_SAFE_CALL(glDisable(GL_DEPTH_TEST));
		GL_SAFE_CALL(glClear(GL_COLOR_BUFFER_BIT));
		GL_SAFE_CALL(glActiveTexture(GL_TEXTURE0));
		m_pGeomFrameBuffer->getAttachment(GL_COLOR_ATTACHMENT0)->bind();
		GL_SAFE_CALL(glActiveTexture(GL_TEXTURE1));
		m_pGeomFrameBuffer->getAttachment(GL_COLOR_ATTACHMENT1)->bind();
		GL_SAFE_CALL(glActiveTexture(GL_TEXTURE2));
		m_pGeomFrameBuffer->getAttachment(GL_COLOR_ATTACHMENT2)->bind();
		GL_SAFE_CALL(glActiveTexture(GL_TEXTURE3));
		m_pGeomFrameBuffer->getAttachment(GL_DEPTH_ATTACHMENT)->bind();
		GL_SAFE_CALL(glActiveTexture(GL_TEXTURE4));
		m_pShadowFrameBuffer->getAttachment(GL_DEPTH_ATTACHMENT)->bind();
		m_Material->use(vScene);
		m_pQuadVAO->Draw();
	}

	void CLightingRenderPass::setMaterial(const std::shared_ptr<CMaterial>& vMaterial)
	{
		m_Material = vMaterial;
	}
}
