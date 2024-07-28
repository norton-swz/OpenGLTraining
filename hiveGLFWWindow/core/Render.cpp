#include "Render.h"
#include <ConfigInterface.h>
#include <UtilityInterface.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <HiveLogger.h>
#include "../primitive/Primitive.h"
#include "../light/PointLight.h"
#include "../material/SolidColorMaterial.h"
#include "../material/SimplePointCloudMaterial.h"
#include "../camera/FPSController.h"
#include "../modelLoader/modelLoader.h"


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

    Status = hiveParseConfig(vAlgorithmConfigFileName, hiveConfig::EConfigType::XML, &m_AlgorithmConfig);
    const hiveConfig::CHiveConfig* Sub1config = m_AlgorithmConfig.findSubconfigByName("gltf_shading");
    const std::string VertShaderPath = Sub1config->getAttribute<std::string>("VERTEX_SHADER").value();
    const std::string FragShaderPath = Sub1config->getAttribute<std::string>("FRAGMENT_SHADER").value();
    m_pMaterial = std::make_shared<CSolidColorMaterial>(VertShaderPath, FragShaderPath);
    m_pRenderPass = std::make_shared<CRenderPass>();

    init(m_pWindow->getWidth(), m_pWindow->getHeight());
}


void hiveWindow::CRender::init(int vInitWidth, int vInitHeight)
{
    m_pScene = std::make_shared<CScene>();
    m_pCamera = std::make_shared<CPerspectiveCamera>();
    m_pCamera->setViewport(vInitWidth, vInitHeight);
    m_pCamera->setSolidColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
    m_pCamera->setFar(1000000.0f);
    m_pScene->setCamera(m_pCamera);
    m_pScene->setLight(std::make_shared<CPointLight>(glm::vec3(10.0f, 10.0f, 10.0f), glm::vec3(300.0f, 300.0f, 300.0f) * 4.0f));

    m_pCamController = std::make_shared<CFPSController>(1.0, 20.0);
    m_pCamController->control(m_pCamera);

    m_pNode = std::make_shared<CNode>();
    //m_pNode->addModel(std::make_shared<CModel>(CPrimitive::createSquare(), m_pMaterial));
    m_pNode = loadModel("E:\\Source\\cpp\\OpenGLTraining\\dragon.gltf", m_pMaterial);

    m_pScene->getRootNode()->clearChilds();
    m_pScene->getRootNode()->addChild(m_pNode);
}

void hiveWindow::CRender::tick()
{
    m_pRenderPass->render(m_pWindow, m_pScene);
}


void hiveWindow::CRender::run()
{
    m_pWindow->run();
}