/*****************************************************************//**
 * \file   Button.h
 * \brief  マウスでクリック可能なボタンUIオブジェクト
 *
 * \author 土居将太郎
 * \date   April 2023
 *********************************************************************/
#pragma once
#include <functional>
#include <memory>
#include "UIObjectBase.h"
#include "UITextBox.h"
namespace AppFrame {
	namespace UI {
		class Button : public UIObjectBase
		{
		public:
			Button();
			~Button();
			void Update(InputManager& input, float deltaSecond)override;
			void Render()override;

			void SetFunction(std::function<void()> function) { _activate = function; }

			void SetIdleColor(unsigned int color) { _idleColor = color; }
			unsigned int GetIdleColor() { return _idleColor; }

			void SetHoverColor(unsigned int color) { _hoverColor = color; }
			unsigned int GetHoverColor() { return _hoverColor; }

			void SetClickedColor(unsigned int color) { _clickedColor = color; }
			unsigned int GetClickedColor() { return _clickedColor; }

			void SetTextBox(std::unique_ptr<UI::TextBox> textBox);
		private:
			std::function<void()> _activate;//クリック時に呼ばれる関数
			enum State { Idle, Hover, Clicked };//待機状態、マウスオーバー状態、マウスクリック状態
			State _state;
			unsigned int _idleColor;//待機状態の色
			unsigned int _hoverColor;//マウスオーバー状態の色
			unsigned int _clickedColor;//マウスクリック状態の色

			std::unique_ptr<TextBox> _textBox;//所有テキストボックス
		};
	}
}