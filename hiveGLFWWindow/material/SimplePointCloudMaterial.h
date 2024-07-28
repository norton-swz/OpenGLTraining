#pragma once

#include "Material.h"
#include "../core/Shader.h"

namespace hiveWindow
{
	class CSimplePointCloudMaterial : public CMaterial
	{
	public:
		CSimplePointCloudMaterial(const std::string& vVertShaderPath, const std::string& vFragShaderPath);
		// Inherited via CMaterial
		void use(const std::shared_ptr<CScene>& vScene, const std::shared_ptr<CNode>& vNode) override;
	private:
		static std::shared_ptr<CShader> m_pShader;
	};
}

