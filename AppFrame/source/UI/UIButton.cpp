/*****************************************************************//**
 * \file   UIButton.cpp
 * \brief  マウスでクリック可能なボタンUIオブジェクト
 *
 * \author 土居将太郎
 * \date   April 2023
 *********************************************************************/
#include "UIButton.h"
#include "CheckCollision.h"
#include "InputManager.h"
#include "Color.h"
namespace AppFrame {
	namespace UI {
		Button::Button()
			:_activate{ nullptr }
			, _state{ State::Idle }
			, _idleColor{ Color::White }
			, _hoverColor{ Color::Gray }
			, _clickedColor{ Color::Yellow }
			, _textBox{ nullptr }
		{
			this->SetNeedUpdate(true);
		}

		Button::~Button()
		{
		}

		void Button::Update(InputManager& input, float deltaSecond)
		{
			if (CheckCollision::Within(this->GetAABB(), input.GetMouseXY())) {
				if (input.GetMouseLeft(InputState::Pressed)) {
					if (_activate != nullptr) {
						_activate();
					}
				}
				if (input.GetMouseLeft(InputState::Hold)) {
					_state = State::Clicked;
				}
				else {
					_state = State::Hover;
				}
			}
			else {
				_state = State::Idle;
			}
			if (_textBox) {
				_textBox->Update(input, deltaSecond);
			}
		}

		void Button::Render()
		{
			auto stateColor = [&]()->unsigned int {
				switch (_state)
				{
				case Button::Idle:
					return _idleColor;
				case Button::Hover:
					return _hoverColor;
				case Button::Clicked:
					return _clickedColor;
				default:
					return 0;
				}
			};

			auto aabb = this->GetAABB();
			DxLib::DrawBox(aabb.min.x, aabb.min.y, aabb.max.x, aabb.max.y, stateColor(), true);
			if (_textBox) {
				_textBox->Render();
			}
		}

		void Button::SetTextBox(std::unique_ptr<UI::TextBox> textBox)
		{
			if (textBox == nullptr) {
				return;
			}
			_textBox = std::move(textBox);
			_textBox->SetAnchor(this->GetAnchor());
			_textBox->SetPosition(this->GetPosition());
		}
	}
}