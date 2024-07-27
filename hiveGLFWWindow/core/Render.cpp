#include "Render.h"
#include <ConfigInterface.h>
#include <UtilityInterface.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <HiveLogger.h>
#include "../core/VertexBuffer.h"

hiveWindow::CRender::CRender()
{
}

hiveWindow::CRender& hiveWindow::CRender::getInstance()
{
    static CRender Instance;
    return Instance;
}

void hiveWindow::CRender::startup(const std::string& vWindowConfigFileName, const std::string& vAlgorithmConfigFileName)
{
    auto Status = hiveConfig::hiveParseConfig(vWindowConfigFileName, hiveConfig::EConfigType::XML, &m_WindowConfig);

    m_pWindow = std::make_shared<hiveWindow::CGLFWWindow>();
    if (!m_pWindow->readFormXML(m_WindowConfig))
    {
        HIVE_LOG_FATAL("Failed to read configuration");
        return;
    }
    if (!m_pWindow->initWindow())
    {
        HIVE_LOG_FATAL("Failed to create GLFWWindow");
        return;
    }

	Status = hiveConfig::hiveParseConfig(vAlgorithmConfigFileName, hiveConfig::EConfigType::XML, &m_AlgorithmConfig);
    const std::string VertShaderPath = m_AlgorithmConfig.getAttribute<std::string>("shader_perpixel_shading_vs|SHADER_SOURCE_FILE").value();
    const std::string FragShaderPath = m_AlgorithmConfig.getAttribute<std::string>("shader_perpixel_shading_fs|SHADER_SOURCE_FILE").value();
    m_pShader = std::make_shared<CShader>(VertShaderPath, FragShaderPath);
    std::vector<float> vertices = {
     -0.5f, -0.5f, 0.0f,   0.0f,  0.0f,  1.0f,  1.0f, 0.0f, 0.0f,// left  bottom
      0.5f, -0.5f, 0.0f,   0.0f,  0.0f,  1.0f,   0.0f, 1.0f, 0.0f,// right bottom
     -0.5f, 0.5f, 0.0f,    0.0f,  0.0f,  1.0f,   0.0f, 0.0f, 1.0f,// left top
     -0.5f, 0.5f, 0.0f,    0.0f,  0.0f,  1.0f,   0.0f, 0.0f, 1.0f,// left top
      0.5f, 0.5f, 0.0f,    0.0f,  0.0f,  1.0f,   1.0f, 0.0f, 0.0f,// right top
      0.5f, -0.5f, 0.0f,   0.0f,  0.0f,  1.0f,   0.0f, 1.0f, 0.0f,// right bottom
    };
    std::vector<int> AttributeLayout = { 3, 3, 3 };

    unsigned int VBO, VAO;
    m_pVertexBuffer = std::make_shared<hiveVertexBuffer::CVertexBuffer>(vertices, AttributeLayout, GL_STATIC_DRAW, GL_TRIANGLES);
}

void hiveWindow::CRender::run()
{
    while (!glfwWindowShouldClose(m_pWindow->getMyWindow()))
    {
        processInput(m_pWindow->getMyWindow());
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        m_pShader->use();
        m_pShader->setUniform("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        m_pShader->setUniform("lightPos", glm::vec3(0.0f, 0.0f, 3.0f));
        m_pShader->setUniform("viewPos", glm::vec3(0.0f, 0.0f, 3.0f));

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)m_pWindow->getWidth() / (float)m_pWindow->getHeight(), 0.1f, 100.0f);
        glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f) + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        m_pShader->setUniform("projection", projection);
        m_pShader->setUniform("view", view);
        glm::mat4 model = glm::mat4(1.0f);
        m_pShader->setUniform("model", model);

        m_pVertexBuffer->Draw();

        glfwSwapBuffers(m_pWindow->getMyWindow());
        glfwPollEvents();
    }

    glfwTerminate();
}

void hiveWindow::CRender::processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
