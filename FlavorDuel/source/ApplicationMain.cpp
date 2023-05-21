#include "ApplicationMain.h"
#include "ModeInGame.h"
#include "ModeTitle.h"
#include "CardDataStruct.h"
namespace {
	Flavor::DeckData TestDeck = {
		"test",
		{{"ドラゴン","炎を吐く"},
		{"大きな亀","頑丈な甲羅にこもって暮らしている"},
		{"兵士","鎧を身に着け、大きな槍を持つ"},
		{"魔法使い","5属性の魔法を操る"},
		{"天使","雲の上に住む存在"},
		{"トレント","森に立ち入った人間を攻撃する"},
		{"僧侶","回復魔法を得意とする"},
		{"ゴブリン","ずる賢く、集団で行動する"},
		{"スライム","雨を吸収して生きている"},
		{"猫","鳴き声は「にゃーん」"}}
	};
}
namespace Flavor {
	ApplicationMain g_oApplicationMain;

	bool ApplicationMain::Initialize(HINSTANCE hInstance)
	{
		if (!ApplicationBase::Initialize(hInstance)) { return false; }
		auto modeServer = AppFrame::ModeServer::GetInstance();
		//modeServer->Add(std::make_unique<ModeInGame>(TestDeck, TestDeck));
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