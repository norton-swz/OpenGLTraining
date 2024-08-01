#include "PointLight.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace hiveWindow
{
	CPointLight::CPointLight(const glm::vec3& vPosition, const glm::vec3& vDiffuseColor)
		:m_Position(vPosition), m_DiffuseColor(vDiffuseColor)
	{
		float near_plane = 1.0f, far_plane = 9.0f;
		glm::mat4 LightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
		glm::mat4 LightView = lookAt(m_Position, glm::vec3(0.1f), glm::vec3(0.0, 1.0, 0.0));
		m_LightSpaceMatrix = LightProjection * LightView;
	}
}
