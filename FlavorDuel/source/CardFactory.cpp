#include "CardFactory.h"
#include "CardObject.h"
namespace Flavor {
	std::unique_ptr<CardObject> CardFactory::CreateCard(CardData data)
	{
		auto card = std::make_unique<CardObject>();
		card->Init();
		card->SetCardName(data.name);
		card->SetAttack(data.attack);
		card->SetDefense(data.defence);
		card->SetImage(data.cg);

		//“K‹X‰üs
		std::string setText{ data.flavorText };
		int oneLineCharNumber = 16;
		int countByte{ 0 };
		for (int i = 0; i < static_cast<int>(data.flavorText.size());) {
			int checkByte = AppFrame::ShiftJISChecker::Check(data.flavorText.at(i));
			countByte += checkByte;
			if (countByte > oneLineCharNumber) {
				setText.insert(i, "\n");
				countByte = 0;
			}
			i += checkByte;
		}
		card->SetCardText(setText);

		return std::move(card);
	}
}

