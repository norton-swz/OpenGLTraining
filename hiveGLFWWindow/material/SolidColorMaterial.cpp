#include "SolidColorMaterial.h"

#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

#include "../core/Scene.h"
#include "../utils/AssetsPath.h"



std::shared_ptr<hiveWindow::CShader> hiveWindow::CSolidColorMaterial::m_pShader{nullptr};

hiveWindow::CSolidColorMaterial::CSolidColorMaterial(const std::string& vVertShaderPath, const std::string& vFragShaderPath)
{
	if (m_pShader == nullptr)
	{
		m_pShader = std::make_shared<CShader>(vVertShaderPath, vFragShaderPath);
	}
}

hiveWindow::CSolidColorMaterial::CSolidColorMaterial(const glm::vec3& vColor) :m_Color(vColor)
{
	if (m_pShader == nullptr)
	{
		std::string Dir = CAssetsPath::getAssetsPath() + "\\shaders\\";
		m_pShader = std::make_shared<CShader>(Dir + "solidColor.vert", Dir + "solidColor.frag");
	}
}

void hiveWindow::CSolidColorMaterial::use(const std::shared_ptr<CScene>& vScene, const std::shared_ptr<CNode>& vNode)
{
	m_pShader->use();
	m_pShader->setUniform("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
	updateLightDirection();
	m_pShader->setUniform("lightdirection", m_LightDirection);

	m_pShader->setUniform("model", vNode->getModelMatrix());
	m_pShader->setUniform("view", vScene->getCamera()->getViewMatrix());
	m_pShader->setUniform("projection", vScene->getCamera()->getProjectionMatrix());
	/*glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
	glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f) + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	m_pShader->setUniform("projection", projection);
	m_pShader->setUniform("view", view);
	glm::mat4 model = glm::mat4(1.0f);
	m_pShader->setUniform("model", model);*/
}



void hiveWindow::CSolidColorMaterial::updateLightDirection()
{
	float Theta = glm::pi<float>() * std::sin(glfwGetTime());
	float Phi = glm::two_pi<float>() * std::cos(glfwGetTime());
	float X = std::sin(Theta) * std::cos(Phi) * 1.5f;
	float Y = std::sin(Theta) * std::sin(Phi) * 1.5f;
	float Z = std::cos(Theta) * 1.5f;
	m_LightDirection = glm::vec3(X, Y, Z);
}