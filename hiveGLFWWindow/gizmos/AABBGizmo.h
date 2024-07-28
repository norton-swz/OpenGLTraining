#pragma once

#include "../core/Node.h"
#include "../base/VertexBuffer.h"
#include "../culling/AABB.h"

namespace hiveWindow
{
	class CAABBGizmo : public CNode
	{
	public:
		CAABBGizmo(const std::shared_ptr<CAABB>& vAABB);
	private:
		std::shared_ptr<CVertexBuffer> __createVAO();
		std::shared_ptr<CAABB> m_pAABB;
	};
}