#include "SimplePointCloudMaterial.h"
#include "../core/Scene.h"
#include "../utils/AssetsPath.h"

namespace hiveWindow
{
	std::shared_ptr<CShader> CSimplePointCloudMaterial::m_pShader{ nullptr };

	CSimplePointCloudMaterial::CSimplePointCloudMaterial(const std::string& vVertShaderPath, const std::string& vFragShaderPath)
	{
		m_pShader = std::make_shared<CShader>(vVertShaderPath, vFragShaderPath);
	}

	void CSimplePointCloudMaterial::use(const std::shared_ptr<CScene>& vScene, const std::shared_ptr<CNode>& vNode)
	{
		m_pShader->use();
		m_pShader->setUniform("uModel", vNode->getModelMatrix());
		m_pShader->setUniform("uView", vScene->getCamera()->getViewMatrix());
		m_pShader->setUniform("uProjection", vScene->getCamera()->getProjectionMatrix());
	}
}