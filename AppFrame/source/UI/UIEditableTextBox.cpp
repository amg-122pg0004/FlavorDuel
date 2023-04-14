/*****************************************************************//**
 * \file   UIEditableTextBox.h
 * \brief  UIキャンバスに配置可能な編集可能なテキストボックス
 *
 * \author 土居将太郎
 * \date   April 2023
 *********************************************************************/
#include "UIEditableTextBox.h"
#include "Color.h"
namespace {
	constexpr int MaxStrLength = 200;
	constexpr int CancelValidFlag = true;
	constexpr int SingleCharOnlyFlag = false;
	constexpr int NumCharOnlyFlag = false;
}

namespace AppFrame {
	namespace UI {
		EditableTextBox::EditableTextBox(std::string text)
			:_text{ text }
			, _font{ -1 }
			, _textColor{ Color::Red }
			, _drawBox{ false }
			, _boxColor{ Color::White }
			, _activate{ false }
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
					SetKeyInputString(_text.c_str(), _inputHandle);
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
			if (this->GetAnchor() == Anchor::Center) {
				aabb.min += this->GetHalfSize();
				int textWidth = GetDrawStringWidth(_text.c_str(), static_cast<int>(_text.size()));
				aabb.min.x -= static_cast<int>(static_cast<float>(textWidth) * 0.5f);
				int textHight{ GetFontSize() };
				if (_font != -1) {
					int textHight = GetFontSizeToHandle(_font);
				}
				aabb.min.y -= static_cast<int>(static_cast<float>(textHight) * 0.5f);
			}

			if (_font == -1) {
				DrawString(aabb.min.x, aabb.min.y, _text.c_str(), _textColor);
			}
			else {
				DrawStringToHandle(aabb.min.x, aabb.min.y, _text.c_str(), _textColor, _font);
			}
		}
		void EditableTextBox::ActivateInput()
		{
			SetActiveKeyInput(_inputHandle);
			_activate = true;
		}
	}
}
