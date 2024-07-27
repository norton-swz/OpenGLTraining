#pragma once
#ifdef MYDLL
#define PORT __declspec(dllexport)
#else
#define PORT __declspec(dllimport)
#endif

#include <HiveConfig.h>

namespace hiveWindow
{
	class PORT CAlgorithmConfig : public hiveConfig::CHiveConfig
	{
	public:
		CAlgorithmConfig();
		~CAlgorithmConfig() = default;

	private:
		void __defineAttributesV() override;
		void __loadDefaultConfigV() override;
	};
}


