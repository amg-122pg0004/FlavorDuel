#include "ModeTitle.h"
#include "LoginUI.h"
#include "RegisterUI.h"
#include "ModeHome.h"
using namespace Flavor;
ModeTitle::ModeTitle()
	:_changeFlag{ false }
	, _nextUI{ TitleUI::Login }
{
}

bool ModeTitle::Initialize()
{
	ModeBase::Initialize();

	auto titleUI = std::make_unique<LoginUI>(*this);
	this->GetUICanvasServer()->Add(std::move(titleUI));
	auto registerUI = std::make_unique<RegisterUI>(*this);
	registerUI->SetActivate(false);
	this->GetUICanvasServer()->Add(std::move(registerUI));
	return false;
}

bool ModeTitle::Terminate()
{
	ModeBase::Terminate();
	return false;
}

bool ModeTitle::Update(InputManager& input)
{
	ModeBase::Update(input);
	if (_changeFlag) {
		ChangeUI();
	}
	return false;
}

bool ModeTitle::Render()
{
	ModeBase::Render();
	return false;
}

bool ModeTitle::Debug()
{
	ModeBase::Debug();
	return false;
}

void Flavor::ModeTitle::ChangeModeHome()
{
	AppFrame::ModeServer::GetInstance()->Add(std::make_unique<ModeHome>());
	AppFrame::ModeServer::GetInstance()->Del(this);
}

void Flavor::ModeTitle::ChangeUI()
{
	_changeFlag = false;
	for (auto&& canvas : this->GetUICanvasServer()->GetObjects()) {
		canvas->SetActivate(false);
	}
	std::string activateUI{""};
	switch (_nextUI)
	{
	case TitleUI::Login:
		activateUI = "Login";
		break;
	case TitleUI::Register:
		activateUI = "Register";
		break;
	default:
		break;
	}
	this->GetUICanvasServer()->Get(activateUI)->SetActivate(true);
}
