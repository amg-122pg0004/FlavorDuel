#pragma once
#include <string>
namespace Flavor {
	struct CardDataPassive
	{
		std::string name;
		std::string flavorText;
	};

	struct CardDataActive
	{
		std::string name;
		std::string flavorText;
		int power;
		std::string tips;
	};
}
