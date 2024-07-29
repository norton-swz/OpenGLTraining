#pragma once

#include <memory>
#include <string>

namespace hiveWindow
{
	class CScene;
	class CNode;
	class CMaterial
	{
	public:
		virtual void use(const std::shared_ptr<CScene>& vScene, const std::shared_ptr<CNode>& vNode) = 0;
		virtual void updateShader(const std::string& vVertShaderPath, const std::string& vFragShaderPath) = 0;
	};
}
