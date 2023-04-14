/*****************************************************************//**
 * \file   UIEditableTextBox.h
 * \brief  UIキャンバスに配置可能な編集可能なテキストボックス
 * 
 * \author 土居将太郎
 * \date   April 2023
 *********************************************************************/
#pragma once
#include <string>
#include "UIObjectBase.h"
namespace AppFrame {
    namespace UI {
        class EditableTextBox : public UIObjectBase
        {
        public:
            EditableTextBox(std::string text);
            ~EditableTextBox();
            void Update(InputManager& input, float deltaSecond)override;
            void Render()override;

            void SetFont(int font) { _font = font; }
            /**
            * \brief テキストボックスの背景色を描画するか
            * \param flag trueの時描画
            */
            void SetDrawBox(bool flag) { _drawBox = flag; }
            /**
             * \brief入力モードをオンにする
             */
            void ActivateInput();
        private:
            std::string _text;
            int _font;
            unsigned int _textColor;
            bool _drawBox;//文字の背景ボックスを描画するか
            unsigned int _boxColor;

            int _inputHandle;//キー入力バッファ
            bool _activate;//入力受付中
        };
    }
}