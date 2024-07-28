#pragma once
#include <memory>
#include <string>
#include <glm/vec3.hpp>
#include "../base/VertexBuffer.h"
#include "../window/GLFWWindow.h"
#include "../material/Material.h"

namespace hiveWindow
{
	class CRenderPass
	{
	public:
		CRenderPass();
		~CRenderPass();

		bool init(const std::string& vAlgorithmConfigFileName);
		void render(const std::shared_ptr<hiveWindow::CGLFWWindow>& vWindow, const std::shared_ptr<CScene>& vScene);

	private:
		std::shared_ptr<CMaterial> m_pMaterial;
		
		std::shared_ptr<CVertexBuffer> m_pVertexBuffer;
		
	};
}
