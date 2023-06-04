#include "ModeHome.h"
#include "HomeUI.h"
#include "ModeMatching.h"
#include "ApplicationMain.h"
#include "ModeDeckEdit.h"
using namespace Flavor;
ModeHome::ModeHome()
{
}

bool ModeHome::Initialize()
{
	ModeBase::Initialize();
	auto titleUI = std::make_unique<HomeUI>(*this);
	this->GetUICanvasServer()->Add(std::move(titleUI));
	return false;
}

bool ModeHome::Terminate()
{
	ModeBase::Terminate();
	return false;
}

bool ModeHome::Update(InputManager& input)
{
	ModeBase::Update(input);
	return false;
}

bool ModeHome::Render()
{
	ModeBase::Render();
	return false;
}

bool ModeHome::Debug()
{
	ModeBase::Debug();
	return false;
}

void ModeHome::OpenMatching()
{
	auto app = AppFrame::ApplicationBase::GetInstance();
	std::vector<CardData> deckData = app->GetAppData()->GetData<UserData>().deck;
	AppFrame::ModeServer::GetInstance()->Add(std::make_unique<ModeMatching>(MatchType::Casual, deckData, *this));
}

void Flavor::ModeHome::ChangeModeDeckEdit()
{
	AppFrame::ModeServer::GetInstance()->Del(this);
	AppFrame::ModeServer::GetInstance()->Add(std::make_unique<ModeDeckEdit>());
}
