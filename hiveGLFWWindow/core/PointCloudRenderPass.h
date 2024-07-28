#pragma once
#include "RenderPass.h"

namespace hiveWindow
{
	class CPointCloudRenderPass :public CRenderPass
	{
	public:
		CPointCloudRenderPass() = default;
		void render(const std::shared_ptr<CScene>& vScene);
	};
}
