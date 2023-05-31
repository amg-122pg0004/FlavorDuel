#include "CardFactory.h"
#include <fstream>
#include <picojson.h>
#include "CardObject.h"
std::ifstream ifs();
namespace {
	constexpr auto CardImageIndexFilePath = "res/CardImageIndex.json";
}

namespace Flavor {
	CardFactory::CardFactory()
	{
		std::ifstream ifs(CardImageIndexFilePath);
		picojson::value json;
		ifs >> json;

		const std::string err = picojson::get_last_error();

		if (!err.empty()) {
			return;
		}
		picojson::object root = json.get<picojson::object>();
		for (auto&& element : root) {
			std::string key = element.first;
			std::string pathData = element.second.get<std::string>();
			_cardImageMap[std::stoi(key)] = pathData;
		}
	}

	std::unique_ptr<CardObject> CardFactory::CreateCard(CardData data)
	{
		auto card = std::make_unique<CardObject>();
		card->SetCardData(data);
		int imageHandle = AppFrame::ImageServer::LoadGraph(_cardImageMap[data.cg]);
		card->SetImage(imageHandle);
		card->Init();

		return std::move(card);
	}
}