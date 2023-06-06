#include "ModeResult.h"
#include "ResultUI.h"
#include "ModeHome.h"
#include "ModeInGame.h"
using namespace Flavor;
ModeResult::ModeResult(ModeInGame& modeInGmame, ResultType type)
	:_type{ type }
	, _modeInGame{ modeInGmame }
{
}

bool ModeResult::Initialize()
{
	ModeBase::Initialize();
	auto resultUI = std::make_unique<ResultUI>(*this, _type);
	this->GetUICanvasServer()->Add(std::move(resultUI));
	return false;
}

bool ModeResult::Terminate()
{
	ModeBase::Terminate();
	return false;
}

bool ModeResult::Update(InputManager& input)
{
	AppFrame::ModeServer::GetInstance()->PauseProcessUnderLayer();
	ModeBase::Update(input);
	return false;
}

bool ModeResult::Render()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	auto app = AppFrame::ApplicationBase::GetInstance();
	DrawBox(0, 0, app->DispSizeW(), app->DispSizeH(), AppFrame::Color::Black, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	ModeBase::Render();
	return false;
}

bool ModeResult::Debug()
{
	ModeBase::Debug();
	return false;
}

void ModeResult::ChangeModeHome()
{
	AppFrame::ModeServer::GetInstance()->Del(&_modeInGame);
	AppFrame::ModeServer::GetInstance()->Del(this);
	AppFrame::ModeServer::GetInstance()->Add(std::make_unique<ModeHome>());

}
