#pragma once

#include "Light.h"

namespace hiveWindow
{
	class CDirectionalLight : public CLight
	{
	public:
		// Inherited via CLight
		glm::vec3 getDiffuseColor() const override;
		glm::vec3 getPosition() const override;
		glm::vec3 getDirection() const override;
	};
}