#pragma once

#include "AlgorithmConfig.h"
#include "Shader.h"

namespace hiveWindow
{
	class CRender
	{
	public:
		static CRender& getInstance();
		void startup(const std::string& vConfigFileName);

	private:
		CRender();
		CRender(const CRender&) = delete;
		CRender& operator=(const CRender&) = delete;
		std::shared_ptr<CShader> m_pShader;
		CAlgorithmConfig m_Config;
	};
}