#pragma once
#include <memory>
#include "CardDataStruct.h"

namespace Flavor {
	class CardObject;
	class CardFactory {
	public:
		std::unique_ptr<CardObject> CreateCard(CardData data);
	};
}