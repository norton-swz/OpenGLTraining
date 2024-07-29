#include "RenderPass.h"
#include "../material/SolidColorMaterial.h"
#include "../primitive/Primitive.h"
#include "../core/Node.h"
#include "../core/Scene.h"

hiveWindow::CRenderPass::CRenderPass()
	:m_pMaterial(nullptr)
{
}

hiveWindow::CRenderPass::~CRenderPass()
{
    m_pMaterial.reset();
}

bool hiveWindow::CRenderPass::init(const std::string& vAlgorithmConfigFileName)
{
	return true;
}

void hiveWindow::CRenderPass::render(const std::shared_ptr<CGLFWWindow>& vWindow, const std::shared_ptr<CScene>& vScene)
{
	//vScene->getCamera()->getFrameBuffer()->bind();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	CNode::traverse(vScene->getRootNode(), [&](const std::shared_ptr<CNode>& vNode) {
		for (const auto& pModel : vNode->getModels())
		{
			pModel->getMaterial()->use(vScene, vNode);
			pModel->getVAO()->Draw();
		}
		});
}

//void hiveWindow::CRenderPass::onViewportChange(int vWidth, int vHeight)
//{
//	m_pFrameBuffer->resize(vWidth, vHeight);
//}


