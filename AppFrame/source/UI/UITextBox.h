/*****************************************************************//**
 * \file   UITextBox.h
 * \brief  UI�L�����o�X�ɔz�u�\�ȃe�L�X�g�{�b�N�X
 *
 * \author �y�������Y
 * \date   April 2023
 *********************************************************************/
#pragma once
#include <string>
#include <functional>
#include "UIObjectBase.h"
namespace AppFrame {
	namespace UI {
		class TextBox : public UIObjectBase
		{
		public:
			TextBox(std::string text);
			~TextBox();
			void Update(InputManager& input, float deltaSecond)override;
			void Render()override;
			void SetFont(int font) { _font = font; }
			/**
			 * \brief �e�L�X�g�{�b�N�X�̔w�i�F��`�悷�邩
			 * \param flag true�̎��`��
			 */
			void SetDrawBox(bool flag) { _drawBox = flag; }

			void SetTextColor(unsigned int color) { _textColor = color; }
			void SetBoxColor(unsigned int color) { _boxColor = color; }

			void SetText(std::string text) { _text = text; }
			void SetBindFunction(std::function<std::string()> function);
		private:
			std::string _text;
			int _font;
			unsigned int _textColor;
			bool _drawBox;
			unsigned int _boxColor;
			std::function<std::string()> _bind;
			float _scale;//�t�H���g�T�C�Y��_size�ɍ��킹��ׂ̃X�P�[���l
		};
	}
}