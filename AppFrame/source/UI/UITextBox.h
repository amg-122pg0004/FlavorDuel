/*****************************************************************//**
 * \file   UITextBox.h
 * \brief  UIキャンバスに配置可能なテキストボックス
 * 
 * \author 土居将太郎
 * \date   April 2023
 *********************************************************************/
#pragma once
#include <string>
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
			 * \brief テキストボックスの背景色を描画するか
			 * \param flag trueの時描画
			 */
			void SetDrawBox(bool flag) { _drawBox = flag; }
		private:
			std::string _text;
			int _font;
			unsigned int _textColor;
			bool _drawBox;
			unsigned int _boxColor;
		};
	}
}