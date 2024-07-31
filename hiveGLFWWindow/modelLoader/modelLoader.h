#pragma once

#include <memory>
#include <string>
#include "../core/Node.h"

namespace hiveWindow
{
	std::shared_ptr<CNode> loadModel(const std::string& vFileName, const std::shared_ptr<CMaterial>& vMaterial);
	//std::shared_ptr<CNode> loadPointCloud(const std::string& vFileName, const std::shared_ptr<CMaterial>& vMaterial);
}