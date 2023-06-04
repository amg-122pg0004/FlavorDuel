#include "CardImagePathLoader.h"
#include <fstream>
#include <picojson.h>
using namespace Flavor;

namespace {
	constexpr auto CardImageIndexFilePath = "res/CardImageIndex.json";
}
CardImagePathLoader::CardImagePathLoader()
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

std::string CardImagePathLoader::GetPath(int id)
{
	if (_cardImageMap.count(id) == 0) {
		return "";
	}

	return 	_cardImageMap[id];
}
