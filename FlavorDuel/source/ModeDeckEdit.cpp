#include "ModeDeckEdit.h"
#include "UserDataStruct.h"
#include "DeckEditUI.h"
#include "CardFactory.h"
#include <functional>
#include "CardObject.h"
#include "ModeHome.h"

using namespace  Flavor;
using InputState = AppFrame::InputState;
namespace {
	constexpr AppFrame::VECTOR2<int> EditCardPosition = { 700,330 };
	constexpr AppFrame::AABB2D<int> NameArea = { { 510,90 },{ 890,130 } };
	constexpr AppFrame::AABB2D<int> TextArea = { { 510,340 },{ 890,510 } };
	constexpr int NameCharacterMax = 20;
	constexpr int TextCharacterMax = 50;
}

ModeDeckEdit::ModeDeckEdit()
	:_cardFactory{ nullptr }
	, _thread{ nullptr }
{
	_inputHandleName = MakeKeyInput(NameCharacterMax, true, false, false);
	_inputHandleText = MakeKeyInput(TextCharacterMax, true, false, false);
}

bool ModeDeckEdit::Initialize()
{
	ModeBase::Initialize();
	_cardFactory.reset(new CardFactory());
	auto userData = AppFrame::ApplicationBase::GetInstance()->GetAppData()->GetData<UserData>();
	_cards = userData.deck;

	auto editUI = std::make_unique<DeckEditUI>(*this);
	this->GetUICanvasServer()->Add(std::move(editUI));
	return false;
}

bool ModeDeckEdit::Terminate()
{
	ModeBase::Terminate();
	return false;
}

bool ModeDeckEdit::Update(InputManager& input)
{
	ModeBase::Update(input);
	if (!_editCard) {
		return false;
	}
	auto inputKeyInputFunction = [&input, this]
	(int inputHandle, bool& activate, AppFrame::AABB2D<int> clickArea, std::string text, std::function<void(std::string)> setter, int charaMax) {
		if (activate) {
			int text = CheckKeyInput(inputHandle);
			if (CheckKeyInput(inputHandle) != 0) {
				char input[100];
				GetKeyInputString(input, inputHandle);
				setter(input);
				activate = false;
			}
		}
		if (input.GetMouseLeft(InputState::Pressed)) {
			if (AppFrame::CheckCollision::Within(clickArea, input.GetMouseXY())) {
				SetKeyInputString(text.c_str(), inputHandle);
				SetActiveKeyInput(inputHandle);
				activate = true;
			}
			else {
				activate = false;
			}
		}
	};
	auto nameSetter = [this](std::string input) { _editCard->SetCardName(input); };
	inputKeyInputFunction(_inputHandleName, _inputActivateName, NameArea, _editCard->GetCardName(), nameSetter, NameCharacterMax);
	auto textSetter = [this](std::string input) { _editCard->SetCardText(input); };
	inputKeyInputFunction(_inputHandleText, _inputActivateText, TextArea, _editCard->GetCardText(), textSetter, TextCharacterMax);

	if (_thread) {
		if (!_thread->IsThreadExec()) {
			if (_thread->GetSuccess()) {
				auto app = AppFrame::ApplicationBase::GetInstance();
				app->GetAppData()->SetData(_thread->GetUserData());
			}
			_thread.release();
		}
	}

	return false;
}

bool ModeDeckEdit::Render()
{
	ModeBase::Render();
	if (_editCard) {
		_editCard->SetPosition(EditCardPosition);
		_editCard->SetScale({ 1.0f,1.0f,1.0f });
		_editCard->Render();
	}
	DrawKeyInputString(NameArea.min.x, 0, _inputHandleName);
	DrawKeyInputString(NameArea.min.x, 0, _inputHandleText);
	return false;
}

bool ModeDeckEdit::Debug()
{
	ModeBase::Debug();
	return false;
}

void ModeDeckEdit::SetEditCard(CardData data)
{
	_editCard = _cardFactory->CreateCard(data);
}

void Flavor::ModeDeckEdit::ApplyEditData()
{
	auto data = _editCard->GetCardData();

	for (auto&& card : _cards) {
		if (data.cg == card.cg) {
			card = data;
			break;
		}
	}

	if (!_thread) {
		auto userData = AppFrame::ApplicationBase::GetInstance()->GetAppData()->GetData<UserData>();
		_thread.reset(new DeckEditThread(userData.id, _cards));
		_thread->ThreadStart();
	}

}

void Flavor::ModeDeckEdit::ChangeModeHome()
{
	AppFrame::ModeServer::GetInstance()->Del(this);
	AppFrame::ModeServer::GetInstance()->Add(std::make_unique<ModeHome>());
}
