#include "DirectionalLight.h"

namespace hiveWindow
{
	glm::vec3 CDirectionalLight::getDiffuseColor() const
	{
		return glm::vec3(0.0f, 0.0f, 0.0f);
	}
	glm::vec3 CDirectionalLight::getPosition() const
	{
		return glm::vec3(0.0f, 0.0f, 0.0f);
	}
	glm::vec3 CDirectionalLight::getDirection() const
	{
		return glm::vec3(0.0f, 0.0f, 0.0f);
	}
}