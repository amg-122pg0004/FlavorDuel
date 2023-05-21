/*****************************************************************//**
 * \file   UIEditableTextBox.h
 * \brief  UIキャンバスに配置可能な編集可能なテキストボックス
 *
 * \author 土居将太郎
 * \date   April 2023
 *********************************************************************/
#include "UIEditableTextBox.h"
#include "Color.h"
#include "CheckCollision.h"
#include "InputManager.h"

using namespace AppFrame::UI;

namespace {
	constexpr int MaxStrLength = 200;
	constexpr int CancelValidFlag = true;
	constexpr int SingleCharOnlyFlag = false;
	constexpr int NumCharOnlyFlag = false;
	constexpr AppFrame::VECTOR2<int> TextPadding = { 2,2 };
	constexpr auto DefaultText = "入力してください";
}


EditableTextBox::EditableTextBox(std::string text)
	:_defaultText{ DefaultText }
	, _defaultTextColor{ Color::Gray }
	, _text{ text }
	, _font{ -1 }
	, _textColor{ Color::Red }
	, _drawBox{ false }
	, _boxColor{ Color::White }
	, _activate{ false }
	, _secret{ false }
{
	this->SetNeedUpdate(true);
	_inputHandle = MakeKeyInput(MaxStrLength, CancelValidFlag, SingleCharOnlyFlag, NumCharOnlyFlag);
}

EditableTextBox::~EditableTextBox()
{
	DeleteKeyInput(_inputHandle);
}

void EditableTextBox::Update(InputManager& input, float deltaSecond)
{
	if (_activate) {
		if (CheckKeyInput(_inputHandle) != 0) {
			char input[MaxStrLength];
			GetKeyInputString(input, _inputHandle);
			_text = input;
			_activate = false;
		}
	}
	if (input.GetMouseLeft(InputState::Pressed)) {
		if (CheckCollision::Within(this->GetAABB(), input.GetMouseXY())) {
			this->ActivateInput();
		}
		else {
			_activate = false;
		}
	}


}

void EditableTextBox::Render()
{
	auto aabb = this->GetAABB();
	if (_drawBox) {
		DrawBox(aabb.min.x, aabb.min.y, aabb.max.x, aabb.max.y, _boxColor, true);
	}
	int textWidth{ 0 };
	if (this->GetAnchor() == Anchor::Center) {
		aabb.min += this->GetHalfSize();
		textWidth = GetDrawStringWidth(_text.c_str(), static_cast<int>(_text.size()));
		aabb.min.x -= static_cast<int>(static_cast<float>(textWidth) * 0.5f);
		int textHight{ GetFontSize() };
		if (_font != -1) {
			int textHight = GetFontSizeToHandle(_font);
		}
		aabb.min.y -= static_cast<int>(static_cast<float>(textHight) * 0.5f);
	}

	//表示文字設定
	auto renderText = _text.c_str();
	if (_activate) {
		char input[MaxStrLength + 1];
		GetKeyInputString(input, _inputHandle);
		renderText = input;
	}
	std::string secretText{};
	if (_secret) {
		int length = static_cast<int>(strlen(renderText));
		for (int i = 0; i < length; ++i) {
			secretText += "●";
		}
		renderText = secretText.c_str();
	}
	auto position = this->GetPosition() - this->GetHalfSize() + TextPadding;

	//表示色設定
	unsigned int color{ _textColor };
	std::string renderTextString(renderText);
	if (renderTextString == "") {
		color = _defaultTextColor;
		renderText = _defaultText.c_str();
	}

	if (_font == -1) {
		DrawString(position.x, position.y, renderText, color);
	}
	else {
		DrawStringToHandle(position.x, position.y, renderText, color, _font);
	}
}

void EditableTextBox::ActivateInput()
{
	SetKeyInputString(_text.c_str(), _inputHandle);
	SetActiveKeyInput(_inputHandle);
	_activate = true;
}
