#pragma once
#include <string>
#include <vector>
namespace Flavor {
	struct CardData
	{
		std::string name;
		std::string flavorText;
		int image;
	};

	struct DeckData
	{
		std::string name;
		std::vector<CardData> cards;
	};
}
