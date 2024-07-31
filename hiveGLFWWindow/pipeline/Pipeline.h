#pragma once

#include "../core/Scene.h"

namespace hiveWindow
{
	class CPipeline
	{
	public:
		virtual void render(const std::shared_ptr<CScene>& vScene) = 0;
		virtual void onViewportChange(int vWidth, int vHeight) {}

	};
}