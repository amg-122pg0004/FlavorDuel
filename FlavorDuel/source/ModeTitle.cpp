#include "ModeTitle.h"
#include "TitleUI.h"
using namespace Flavor;
ModeTitle::ModeTitle()
{
}

bool ModeTitle::Initialize()
{
    ModeBase::Initialize();
    auto titleUI = std::make_unique<TitleUI>(*this);
    this->GetUICanvasServer()->Add(std::move(titleUI));
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

void ModeTitle::Login(std::string userName, std::string password)
{
    return;
}

void ModeTitle::Register(std::string userName, std::string password)
{
    return;
}

void ModeTitle::QuitGame()
{
    return;
}
