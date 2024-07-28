#pragma once

#include <memory>

namespace hiveWindow
{
	class CScene;
	class CNode;
	class CMaterial
	{
	public:
		virtual void use(const std::shared_ptr<CScene>& vScene, const std::shared_ptr<CNode>& vNode) = 0;
	};
}