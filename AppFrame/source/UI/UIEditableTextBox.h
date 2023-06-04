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
            EditableTextBox(std::string text, int maxStrLength, int cancelValidFlag, int singleCharOnlyFlag, int numCharOnlyFlag);
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

            /**
             * \brief 非表示モード(文字が伏せられる)を設定する
             * \param flag オンオフ
             */
            void SetSecret(bool flag) { _secret = flag; }
            bool GetSecret() { return _secret; }

            std::string GetText() { return _text; }

            void SetDefaultText(std::string text) { _defaultText = text; }
            void SetTextColor(unsigned int color) { _textColor = color; }
        private:
            std::string _defaultText;//入力が無い場合の表示テキスト
            std::string _text;
            int _font;
            unsigned int _defaultTextColor;
            unsigned int _textColor;
            bool _drawBox;//文字の背景ボックスを描画するか
            unsigned int _boxColor;

            int _inputHandle;//キー入力バッファ
            bool _activate;//入力受付中
            bool _secret;//伏字モード
        };
    }
}