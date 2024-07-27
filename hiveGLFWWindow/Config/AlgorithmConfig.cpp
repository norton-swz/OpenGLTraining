#include "AlgorithmConfig.h"

hiveWindow::CAlgorithmConfig::CAlgorithmConfig()
{
	__defineAttributesV();
}

void hiveWindow::CAlgorithmConfig::__defineAttributesV()
{
	_defineAttribute("SHADER", hiveConfig::EConfigDataType::ATTRIBUTE_SUBCONFIG);
	_defineAttribute("SHADER_SOURCE_FILE", hiveConfig::EConfigDataType::ATTRIBUTE_STRING);
	_defineAttribute("RENDER_ALGORITHM", hiveConfig::EConfigDataType::ATTRIBUTE_SUBCONFIG);
	_defineAttribute("RENDER_PASS", hiveConfig::EConfigDataType::ATTRIBUTE_SUBCONFIG);
	_defineAttribute("VERTEX_SHADER", hiveConfig::EConfigDataType::ATTRIBUTE_STRING);
	_defineAttribute("FRAGMENT_SHADER", hiveConfig::EConfigDataType::ATTRIBUTE_STRING);
}

void hiveWindow::CAlgorithmConfig::__loadDefaultConfigV()
{
	/*CAlgorithmConfig VertShaderSubConfig, FragShaderSubConfig, AlgoriSubConfig, RenderPassSubConfig;
	VertShaderSubConfig.setName("shader_perpixel_shading_vs");
	VertShaderSubConfig.setAttribute("SHADER_SOURCE_FILE", std::string("..\\OpenGLTraining\\2.2.basic_lighting.vs"));
	m_pVertShaderSubConfig = dynamic_cast<CAlgorithmConfig*>(this->addSubconfig(&VertShaderSubConfig));
	FragShaderSubConfig.setName("shader_perpixel_shading_fs");
	FragShaderSubConfig.setAttribute("SHADER_SOURCE_FILE", std::string("..\\OpenGLTraining\\2.2.basic_lighting.fs"));
	m_pFragShaderSubConfig = dynamic_cast<CAlgorithmConfig*>(this->addSubconfig(&FragShaderSubConfig));
	AlgoriSubConfig.setName("PerpixelShading");
	m_pAlgoriSubConfig = dynamic_cast<CAlgorithmConfig*>(this->addSubconfig(&AlgoriSubConfig));
	RenderPassSubConfig.setName("perpixel_shading");
	RenderPassSubConfig.setAttribute("VERTEX_SHADER", std::string("shader_perpixel_shading_vs"));
	RenderPassSubConfig.setAttribute("FRAGMENT_SHADER", std::string("shader_perpixel_shading_fs"));
	m_pRenderPassSubConfig = dynamic_cast<CAlgorithmConfig*>(m_pAlgoriSubConfig->addSubconfig(&RenderPassSubConfig));*/
}