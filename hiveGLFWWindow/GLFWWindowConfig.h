#pragma once
#ifdef MYDLL
#define PORT __declspec(dllexport)
#else
#define PORT __declspec(dllimport)
#endif

#include <HiveConfig.h>

namespace hiveWindow
{
	//TODO  不能将整个类暴露给外部
	class PORT CGLFWWindowConfig : public hiveConfig::CHiveConfig
	{
	public:
		CGLFWWindowConfig();
		~CGLFWWindowConfig() = default;

	private:
		void __defineAttributesV() override;
		void __loadDefaultConfigV() override;
	};
}


