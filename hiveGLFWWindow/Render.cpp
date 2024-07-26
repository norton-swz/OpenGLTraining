#include "Render.h"
#include <ConfigInterface.h>

hiveWindow::CRender& hiveWindow::CRender::getInstance()
{
    static CRender Instance;
    return Instance;
}

void hiveWindow::CRender::startup(const std::string& vConfigFileName)
{
    auto Status = hiveConfig::hiveParseConfig(vConfigFileName, hiveConfig::EConfigType::XML, &m_Config);

    CAlgorithmConfig* pVertShaderSubConfig = dynamic_cast<CAlgorithmConfig*>(m_Config.findSubconfigByName("shader_perpixel_shading_vs"));
    CAlgorithmConfig* pFragShaderSubConfig = dynamic_cast<CAlgorithmConfig*>(m_Config.findSubconfigByName("shader_perpixel_shading_fs"));
    m_pShader = std::make_shared<CShader>(pVertShaderSubConfig->getAttribute<std::string>("SHADER_SOURCE_FILE").value(), pFragShaderSubConfig->getAttribute<std::string>("SHADER_SOURCE_FILE").value());
}

hiveWindow::CRender::CRender()
{

}