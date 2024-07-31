#pragma once
#include <glad/glad.h>

namespace hiveWindow
{
	class CTexture
	{
	public:
		virtual GLuint getID() const = 0;
		virtual void bind() const = 0;
	};
}
