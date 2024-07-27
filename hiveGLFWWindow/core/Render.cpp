#include "Render.h"
#include <ConfigInterface.h>
#include <UtilityInterface.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <HiveLogger.h>
#include "../core/VertexBuffer.h"
#include "../primitive/Primitive.h"


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

    m_pRenderPass = std::make_shared<CRenderPass>();
    m_pRenderPass->init(vAlgorithmConfigFileName);

}

void hiveWindow::CRender::run()
{
    while (!glfwWindowShouldClose(m_pWindow->getMyWindow()))
    {
        processInput(m_pWindow->getMyWindow());
        m_pRenderPass->updateLightPosition();
        m_pRenderPass->render(m_pWindow);

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
