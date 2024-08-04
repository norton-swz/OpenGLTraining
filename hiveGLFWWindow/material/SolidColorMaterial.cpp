#include "SolidColorMaterial.h"

#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

#include "../core/Scene.h"
#include "../utils/AssetsPath.h"



std::shared_ptr<hiveWindow::CShader> hiveWindow::CSolidColorMaterial::m_pShader{nullptr};

hiveWindow::CSolidColorMaterial::CSolidColorMaterial(const std::string& vVertShaderPath, const std::string& vFragShaderPath)
{
	m_pShader = std::make_shared<CShader>(vVertShaderPath, vFragShaderPath);
}

//hiveWindow::CSolidColorMaterial::CSolidColorMaterial(const glm::vec3& vColor) :m_Color(vColor)
//{
//	if (m_pShader == nullptr)
//	{
//		std::string Dir = CAssetsPath::getAssetsPath() + "\\shaders\\";
//		m_pShader = std::make_shared<CShader>(Dir + "solidColor.vert", Dir + "solidColor.frag");
//	}
//}

void hiveWindow::CSolidColorMaterial::use(const std::shared_ptr<CScene>& vScene)
{
	m_pShader->use();
	m_pShader->setUniform("lightColor", glm::vec3(300.0f, 300.0f, 300.0f));
	m_pShader->setUniform("lightPosition", vScene->getLight()->getPosition());
	m_pShader->setUniform("cameraPosition", vScene->getCamera()->getWorldPos());
	m_pShader->setUniform("lightspacematrix", vScene->getLight()->getLightSpaceMatrix());
	m_pShader->setUniform("metallic", 0.9f);
	m_pShader->setUniform("roughness", 0.1f);
	m_pShader->setUniform("ao", 1.0f);
	//updateLightDirection();
	//m_pShader->setUniform("lightdirection", m_LightDirection);
	m_pShader->setUniform("gPosition", 0);
	m_pShader->setUniform("gNormal", 1);
	m_pShader->setUniform("gAlbedoSpec", 2);
	m_pShader->setUniform("gDepth", 3);
	m_pShader->setUniform("sDepth", 4);
	//m_pShader->setUniform("lightdirection", glm::vec3(0.0, 0.0, 3.0));

	/*m_pShader->setUniform("model", vNode->getModelMatrix());
	m_pShader->setUniform("view", vScene->getCamera()->getViewMatrix());
	m_pShader->setUniform("projection", vScene->getCamera()->getProjectionMatrix());*/
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

void hiveWindow::CSolidColorMaterial::updateShader(const std::string& vVertShaderPath, const std::string& vFragShaderPath)
{
	m_pShader = std::make_shared<CShader>(vVertShaderPath, vFragShaderPath);
}
