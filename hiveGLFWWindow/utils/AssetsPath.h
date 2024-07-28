#pragma once

#include <string>

namespace hiveWindow
{
	class CAssetsPath
	{
	public:
		static const std::string& getAssetsPath();
		static std::string extractFileName(const std::string& vFilePath);
	private:
		static std::string m_AssetsPath;
	};
}