#include "GLFWWindowConfig.h"

hiveWindow::CGLFWWindowConfig::CGLFWWindowConfig()
{
	__defineAttributesV();
}

void hiveWindow::CGLFWWindowConfig::__defineAttributesV()
{
	_defineAttribute("Width", hiveConfig::EConfigDataType::ATTRIBUTE_INT);
	_defineAttribute("Height", hiveConfig::EConfigDataType::ATTRIBUTE_INT);
	_defineAttribute("MajorVersion", hiveConfig::EConfigDataType::ATTRIBUTE_INT);
	_defineAttribute("MinorVersion", hiveConfig::EConfigDataType::ATTRIBUTE_INT);
	_defineAttribute("WindowName", hiveConfig::EConfigDataType::ATTRIBUTE_STRING);
	_defineAttribute("UseCoreProfile", hiveConfig::EConfigDataType::ATTRIBUTE_BOOL);
}

void hiveWindow::CGLFWWindowConfig::__loadDefaultConfigV()
{
	setAttribute("Width", 800);
	setAttribute("Height", 600);
	setAttribute("MajorVersion", 3);
	setAttribute("MinorVersion", 3);
	setAttribute("WindowName", std::string("Wang and Sun Window"));
	setAttribute("UseCoreProfile", true);
}
