/*****************************************************************//**
 * \file   Button.h
 * \brief  �}�E�X�ŃN���b�N�\�ȃ{�^��UI�I�u�W�F�N�g
 *
 * \author �y�������Y
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
			std::function<void()> _activate;//�N���b�N���ɌĂ΂��֐�
			enum State { Idle, Hover, Clicked };//�ҋ@��ԁA�}�E�X�I�[�o�[��ԁA�}�E�X�N���b�N���
			State _state;
			unsigned int _idleColor;//�ҋ@��Ԃ̐F
			unsigned int _hoverColor;//�}�E�X�I�[�o�[��Ԃ̐F
			unsigned int _clickedColor;//�}�E�X�N���b�N��Ԃ̐F

			std::unique_ptr<TextBox> _textBox;//���L�e�L�X�g�{�b�N�X
		};
	}
}