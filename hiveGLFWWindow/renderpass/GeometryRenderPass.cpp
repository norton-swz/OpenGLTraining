#include "GeometryRenderPass.h"
#include "../primitive/Primitive.h"
#include "../utils/safe.h"

namespace hiveWindow
{
	CGeometryRenderPass::CGeometryRenderPass(const std::string& vVertShaderPath, const std::string& vFragShaderPath)
		:
		m_pGeoPassShader(std::make_shared<CShader>(vVertShaderPath, vFragShaderPath))
	{
	}

	void CGeometryRenderPass::render(const std::shared_ptr<CScene>& vScene)
	{
		m_pFrameBuffer->bind();
		GL_SAFE_CALL(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
		GL_SAFE_CALL(glEnable(GL_DEPTH_TEST));
		GL_SAFE_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		m_pGeoPassShader->use();
		m_pGeoPassShader->setUniform("view", vScene->getCamera()->getViewMatrix());
		m_pGeoPassShader->setUniform("projection", vScene->getCamera()->getProjectionMatrix());
		CNode::traverse(vScene->getRootNode(), [&](const std::shared_ptr<CNode>& vNode){
				m_pGeoPassShader->setUniform("model", vNode->getModelMatrix());
				for (const auto& pModel : vNode->getModels())
				{
					pModel->getVAO()->Draw();
				}
		});
	}

	void CGeometryRenderPass::_setupFrameBuffer(int vWidth, int vHeight)
	{
		m_pFrameBuffer = std::make_shared<CFrameBuffer>();
		m_pFrameBuffer->bind();
		// - Position color buffer
		const auto& pPositionTex = std::make_shared<CTexture2D>(vWidth, vHeight, GL_RGB16F, GL_RGB, GL_FLOAT);
		pPositionTex->setParameters(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		pPositionTex->setParameters(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		m_pFrameBuffer->setAttachment(GL_COLOR_ATTACHMENT0, pPositionTex);
		// - Normal color buffer
		const auto& pNormalTex = std::make_shared<CTexture2D>(vWidth, vHeight, GL_RGB16F, GL_RGB, GL_FLOAT);
		pNormalTex->setParameters(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		pNormalTex->setParameters(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		m_pFrameBuffer->setAttachment(GL_COLOR_ATTACHMENT1, pNormalTex);
		// - Al
		const auto& pAlbedoSpec = std::make_shared<CTexture2D>(vWidth, vHeight, GL_RGBA, GL_RGBA, GL_FLOAT);
		pAlbedoSpec->setParameters(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		pAlbedoSpec->setParameters(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		m_pFrameBuffer->setAttachment(GL_COLOR_ATTACHMENT2, pAlbedoSpec);
		// - Tell OpenGL which color attachments we'll use (of this framebuffer) for rendering
		m_pFrameBuffer->setDrawAttachments(std::vector<GLenum>{GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2});
		// - Create and attach depth buffer (renderbuffer)
		const auto& pDepthTex = std::make_shared<CTexture2D>(vWidth, vHeight, GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE);
		pDepthTex->setParameters(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		pDepthTex->setParameters(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		m_pFrameBuffer->setAttachment(GL_DEPTH_ATTACHMENT, pDepthTex);
		// - Finally check if framebuffer is complete
		CFrameBuffer::check();
		m_pFrameBuffer->unbind();
	}
}