#include "ApplicationMain.h"
#include "ModeInGame.h"
#include "CardDataStruct.h"
namespace {
	Flavor::DeckData TestDeck = {
		"test",
		{{"�h���S��","����f��"},
		{"�傫�ȋT","���ȍb���ɂ������ĕ�炵�Ă���"},
		{"���m","�Z��g�ɒ����A�傫�ȑ�������"},
		{"���@�g��","5�����̖��@�𑀂�"},
		{"�V�g","�_�̏�ɏZ�ޑ���"},
		{"�g�����g","�X�ɗ����������l�Ԃ��U������"},
		{"�m��","�񕜖��@�𓾈ӂƂ���"},
		{"�S�u����","���錫���A�W�c�ōs������"},
		{"�X���C��","�J���z�����Đ����Ă���"},
		{"�L","�����́u�ɂ�[��v"}}
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