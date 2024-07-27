#pragma once
#include <HiveConfig.h>

namespace hiveWindow
{
	class CGLFWWindowConfig : public hiveConfig::CHiveConfig
	{
	public:
		CGLFWWindowConfig();
		~CGLFWWindowConfig() = default;

	private:
		void __defineAttributesV() override;
		void __loadDefaultConfigV() override;
	};
}


