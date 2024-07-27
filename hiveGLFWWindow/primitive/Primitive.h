#pragma once
#include <memory>

namespace hiveWindow
{
	class CVertexBuffer;
	class CPrimitive
	{
	public:
		static std::shared_ptr<CVertexBuffer> createSquare();
	};
}
