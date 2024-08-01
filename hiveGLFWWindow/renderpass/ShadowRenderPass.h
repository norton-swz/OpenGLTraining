#pragma once
#include "RenderPass.h"
#include "../core/Shader.h"

namespace hiveWindow
{
	class CShadowRenderPass :public CRenderPass
	{
	public:
		CShadowRenderPass(const std::string& vVertShaderPath, const std::string& vFragShaderPath);
		void render(const std::shared_ptr<CScene>& vScene) override;
	protected:
		void _setupFrameBuffer(int vWidth, int vHeight) override;
	private:
		std::shared_ptr<CShader> m_pShadowPassShader;
	};
}


