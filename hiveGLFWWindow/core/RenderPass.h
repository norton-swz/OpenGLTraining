#pragma once
#include <memory>
#include <string>
#include <glm/vec3.hpp>

#include "../Config/AlgorithmConfig.h"
#include "../core/VertexBuffer.h"
#include "../window/GLFWWindow.h"

namespace hiveWindow
{
	class CShader;
	class CRenderPass
	{
	public:
		CRenderPass();
		~CRenderPass();

		bool init(const std::string& vAlgorithmConfigFileName);
		void render(const std::shared_ptr<hiveWindow::CGLFWWindow>& vWindow);
		void updateLightPosition();

	private:
		std::shared_ptr<CShader> m_pShader;
		CAlgorithmConfig m_AlgorithmConfig;
		std::shared_ptr<CVertexBuffer> m_pVertexBuffer;
		glm::vec3 m_LightPosition;
	};
}
