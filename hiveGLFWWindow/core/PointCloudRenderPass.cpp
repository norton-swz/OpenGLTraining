#include "PointCloudRenderPass.h"

#include <glm/vec4.hpp>
#include "Scene.h"
#include "../utils/safe.h"

namespace hiveWindow
{
	void CPointCloudRenderPass::render(const std::shared_ptr<CScene>& vScene)
	{
		vScene->getCamera()->getFrameBuffer()->bind();
		glm::vec4 SolidColor = vScene->getCamera()->getSolidColor();
		GL_SAFE_CALL(glClearColor(SolidColor.x, SolidColor.y, SolidColor.z, SolidColor.w));
		GL_SAFE_CALL(glEnable(GL_DEPTH_TEST));
		GL_SAFE_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		GL_SAFE_CALL(glPointSize(2.0f));
		CNode::traverse(vScene->getRootNode(), [&](const std::shared_ptr<CNode>& vNode) {
			for (const auto& pModel : vNode->getModels())
			{
				pModel->getMaterial()->use(vScene, vNode);
				pModel->getVAO()->Draw();
			}
			});
	}
}
