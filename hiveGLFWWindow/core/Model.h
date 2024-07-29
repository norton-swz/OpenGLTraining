#pragma once

#include <memory>
#include "../base/VertexBuffer.h"
#include "../material/Material.h"

namespace hiveWindow
{
	class CModel
	{
	public:
		CModel(const std::shared_ptr<CVertexBuffer>& vVAO, const std::shared_ptr<CMaterial>& vMaterial)
			:m_pVAO(vVAO), m_pMaterial(vMaterial) {}
		const std::shared_ptr<CVertexBuffer>& getVAO() const { return m_pVAO; }
		const std::shared_ptr<CMaterial>& getMaterial() const { return m_pMaterial; }
		void updateMaterial(const std::string& vVertShaderPath, const std::string& vFragShaderPath) const { m_pMaterial->updateShader(vVertShaderPath, vFragShaderPath); }
	private:
		std::shared_ptr<CVertexBuffer> m_pVAO;
		std::shared_ptr<CMaterial> m_pMaterial;
	};
}