#include "ApplicationMain.h"
#include "ModeInGame.h"
#include "CardDataStruct.h"
namespace {
	Flavor::DeckData TestDeck = {
		"test",
		{{"ƒhƒ‰ƒSƒ“","‰Š‚ð“f‚­"},
		{"‘å‚«‚È‹T","Šæä‚Èb—…‚É‚±‚à‚Á‚Ä•é‚ç‚µ‚Ä‚¢‚é"},
		{"•ºŽm","ŠZ‚ðg‚É’…‚¯A‘å‚«‚È‘„‚ðŽ‚Â"},
		{"–‚–@Žg‚¢","5‘®«‚Ì–‚–@‚ð‘€‚é"},
		{"“VŽg","‰_‚Ìã‚ÉZ‚Þ‘¶Ý"},
		{"ƒgƒŒƒ“ƒg","X‚É—§‚¿“ü‚Á‚½lŠÔ‚ðUŒ‚‚·‚é"},
		{"‘m—µ","‰ñ•œ–‚–@‚ð“¾ˆÓ‚Æ‚·‚é"},
		{"ƒSƒuƒŠƒ“","‚¸‚éŒ«‚­AW’c‚Ås“®‚·‚é"},
		{"ƒXƒ‰ƒCƒ€","‰J‚ð‹zŽû‚µ‚Ä¶‚«‚Ä‚¢‚é"},
		{"”L","–Â‚«º‚Íu‚É‚á[‚ñv"}}
	};
}
namespace Flavor {
	ApplicationMain g_oApplicationMain;

	bool ApplicationMain::Initialize(HINSTANCE hInstance)
	{
		if (!ApplicationBase::Initialize(hInstance)) { return false; }
		auto modeServer = AppFrame::ModeServer::GetInstance();
		modeServer->Add(std::make_unique<ModeInGame>(TestDeck, TestDeck));
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