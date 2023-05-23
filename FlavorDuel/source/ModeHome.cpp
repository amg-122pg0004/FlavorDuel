#include "ModeHome.h"
#include "HomeUI.h"
using namespace Flavor;
ModeHome::ModeHome()
{
}

bool ModeHome::Initialize()
{
	ModeBase::Initialize();
	auto titleUI = std::make_unique<HomeUI>();
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
