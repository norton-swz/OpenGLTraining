#include "RenderPass.h"
#include <ConfigInterface.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "Shader.h"
#include "../core/VertexBuffer.h"
#include "../primitive/Primitive.h"

hiveWindow::CRenderPass::CRenderPass()
	:m_pShader(nullptr)
{
}

hiveWindow::CRenderPass::~CRenderPass()
{
	m_pShader.reset();
	m_pVertexBuffer.reset();
}

bool hiveWindow::CRenderPass::init(const std::string& vAlgorithmConfigFileName)
{
	auto Status = hiveConfig::hiveParseConfig(vAlgorithmConfigFileName, hiveConfig::EConfigType::XML, &m_AlgorithmConfig);
    const hiveConfig::CHiveConfig* Sub1config = m_AlgorithmConfig.findSubconfigByName("perpixel_shading");
    const std::string VertShaderPath = Sub1config->getAttribute<std::string>("VERTEX_SHADER").value();
    const std::string FragShaderPath = Sub1config->getAttribute<std::string>("FRAGMENT_SHADER").value();
	m_pShader = std::make_shared<hiveWindow::CShader>(VertShaderPath, FragShaderPath);
	m_pVertexBuffer = CPrimitive::createSquare();
	return true;
}

void hiveWindow::CRenderPass::render(const std::shared_ptr<hiveWindow::CGLFWWindow>& vWindow)
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    m_pShader->use();
    m_pShader->setUniform("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
    m_pShader->setUniform("lightPos", m_LightPosition);

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)vWindow->getWidth() / (float)vWindow->getHeight(), 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f) + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    m_pShader->setUniform("projection", projection);
    m_pShader->setUniform("view", view);
    glm::mat4 model = glm::mat4(1.0f);
    m_pShader->setUniform("model", model);

    m_pVertexBuffer->Draw();
}

void hiveWindow::CRenderPass::updateLightPosition()
{
    float X = 1.0f + sin(glfwGetTime()) * 2.0f;
    float Y = sin(glfwGetTime() / 2.0f) * 1.0f;
    float Z = 3.0f;
    m_LightPosition = glm::vec3(X, Y, Z);
}
