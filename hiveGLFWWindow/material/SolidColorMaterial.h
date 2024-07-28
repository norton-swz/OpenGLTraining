#pragma once

#include "Material.h"
#include "../core/Shader.h"

namespace hiveWindow
{
	class CSolidColorMaterial : public CMaterial
	{
	public:
		CSolidColorMaterial(const std::string& vVertShaderPath, const std::string& vFragShaderPath);
		CSolidColorMaterial(const glm::vec3& vColor);
		// Inherited via CMaterial
		void use(const std::shared_ptr<CScene>& vScene, const std::shared_ptr<CNode>& vNode) override;
		void updateLightDirection();
	private:
		glm::vec3 m_Color;
		static std::shared_ptr<CShader> m_pShader;
		glm::vec3 m_LightDirection;
	};
}