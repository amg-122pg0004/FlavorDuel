#include "CardFactory.h"
#include <fstream>
#include <picojson.h>
#include "CardObject.h"
namespace Flavor {
	CardFactory::CardFactory()
	{
		_pathLoader.reset(new CardImagePathLoader());
	}

	std::unique_ptr<CardObject> CardFactory::CreateCard(CardData data)
	{
		
		auto card = std::make_unique<CardObject>();
		card->SetCardData(data);
		auto cardCgPath = _pathLoader->GetPath(data.cg);
		int imageHandle = AppFrame::ImageServer::LoadGraph(cardCgPath);
		card->SetImage(imageHandle);
		card->Init();
		return std::move(card);
		
	}
}