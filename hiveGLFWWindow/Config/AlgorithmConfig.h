#pragma once
#include <HiveConfig.h>

namespace hiveWindow
{
	class CAlgorithmConfig : public hiveConfig::CHiveConfig
	{
	public:
		CAlgorithmConfig();
		~CAlgorithmConfig() = default;

	private:
		void __defineAttributesV() override;
		void __loadDefaultConfigV() override;
	};
}


