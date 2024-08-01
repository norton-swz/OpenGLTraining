#include "ShadowRenderPass.h"
#include "../utils/safe.h"

hiveWindow::CShadowRenderPass::CShadowRenderPass(const std::string& vVertShaderPath, const std::string& vFragShaderPath)
	:m_pShadowPassShader(std::make_shared<CShader>(vVertShaderPath, vFragShaderPath))
{
}

void hiveWindow::CShadowRenderPass::render(const std::shared_ptr<CScene>& vScene)
{
	m_pFrameBuffer->bind();
	GL_SAFE_CALL(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
	GL_SAFE_CALL(glEnable(GL_DEPTH_TEST));
	GL_SAFE_CALL(glClear(GL_DEPTH_BUFFER_BIT));
	m_pShadowPassShader->use();
	m_pShadowPassShader->setUniform("lightSpaceMatrix", vScene->getLight()->getLightSpaceMatrix());
	CNode::traverse(vScene->getRootNode(), [&](const std::shared_ptr<CNode>& vNode) {
		m_pShadowPassShader->setUniform("model", vNode->getModelMatrix());
		for (const auto& pModel : vNode->getModels())
		{
			pModel->getVAO()->Draw();
		}
		});
}

void hiveWindow::CShadowRenderPass::_setupFrameBuffer(int vWidth, int vHeight)
{
	m_pFrameBuffer = std::make_shared<CFrameBuffer>();
	m_pFrameBuffer->bind();
	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	const auto& pDepthTex = std::make_shared<CTexture2D>(SHADOW_WIDTH, SHADOW_HEIGHT, GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE);
	pDepthTex->setParameters(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	pDepthTex->setParameters(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	pDepthTex->setParameters(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	pDepthTex->setParameters(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	pDepthTex->setParameters(GL_TEXTURE_BORDER_COLOR, borderColor);
	m_pFrameBuffer->setAttachment(GL_DEPTH_ATTACHMENT, pDepthTex);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	CFrameBuffer::check();
	m_pFrameBuffer->unbind();
}
