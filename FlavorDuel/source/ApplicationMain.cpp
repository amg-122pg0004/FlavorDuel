#include "ApplicationMain.h"
#include "ModeInGame.h"
#include "ModeTitle.h"
#include "ModeHome.h"
#include "UserDataStruct.h"
#include "CardDataStruct.h"


namespace Flavor {
	ApplicationMain g_oApplicationMain;

	ApplicationMain::ApplicationMain() :_debug{ false }
	{
	}

	bool ApplicationMain::Initialize(HINSTANCE hInstance)
	{
		if (!ApplicationBase::Initialize(hInstance)) { return false; }
		UserData data;
		this->GetAppData()->SetData(data);

		auto modeServer = AppFrame::ModeServer::GetInstance();
		//modeServer->Add(std::make_unique<ModeInGame>(TestDeck, TestDeck));
		modeServer->Add(std::make_unique<ModeTitle>());
		//modeServer->Add(std::make_unique<ModeHome>());
		return true;
	}
	bool ApplicationMain::Input()
	{
		ApplicationBase::Input();
		return false;
	}
	bool ApplicationMain::Update()
	{
		if (_inputManager->GetKeyAt(AppFrame::InputState::Pressed)) {
			_debug = !_debug;
		}
		ApplicationBase::Update();
		return false;
	}
	bool ApplicationMain::Render()
	{
		ApplicationBase::Render();
		if (_debug) {
			Debug();
		}
		return false;
	}
	bool ApplicationMain::Debug()
	{
		ApplicationBase::Debug();
		return false;
	}
}