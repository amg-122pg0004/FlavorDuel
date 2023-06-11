#include "ApplicationMain.h"
#include "ModeInGame.h"
#include "ModeTitle.h"
#include "ModeHome.h"
#include "UserDataStruct.h"
#include "CardDataStruct.h"

namespace {
	constexpr auto GenshinGothic16Path = "res/font/GenshinGothic-monoB4S16.dft";
	constexpr auto GenshinGothic32Path = "res/font/GenshinGothic-monoB4S32.dft";
	constexpr auto DartsFontPath = "res/font/GenshinGothic-monoB4S32.dft";
}

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

		AppFrame::FontServer::LoadFont("GGothic16",GenshinGothic16Path);
		AppFrame::FontServer::LoadFont("GGothic32",GenshinGothic32Path);
		AppFrame::FontServer::LoadFont("Darts32", DartsFontPath);

		auto modeServer = AppFrame::ModeServer::GetInstance();
		modeServer->Add(std::make_unique<ModeTitle>());
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