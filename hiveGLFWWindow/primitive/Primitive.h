#pragma once
#include <memory>

namespace hiveWindow
{
	class CVertexBuffer;
	class CPrimitive
	{
	public:
		static std::shared_ptr<CVertexBuffer> createSquare();
		static std::shared_ptr<CVertexBuffer> createQuad();
		static std::shared_ptr<CVertexBuffer> createFloor();
	};
}
