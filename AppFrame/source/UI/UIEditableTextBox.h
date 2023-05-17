/*****************************************************************//**
 * \file   UIEditableTextBox.h
 * \brief  UI�L�����o�X�ɔz�u�\�ȕҏW�\�ȃe�L�X�g�{�b�N�X
 * 
 * \author �y�������Y
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
            * \brief �e�L�X�g�{�b�N�X�̔w�i�F��`�悷�邩
            * \param flag true�̎��`��
            */
            void SetDrawBox(bool flag) { _drawBox = flag; }
            /**
             * \brief���̓��[�h���I���ɂ���
             */
            void ActivateInput();
        private:
            std::string _text;
            int _font;
            unsigned int _textColor;
            bool _drawBox;//�����̔w�i�{�b�N�X��`�悷�邩
            unsigned int _boxColor;

            int _inputHandle;//�L�[���̓o�b�t�@
            bool _activate;//���͎�t��
        };
    }
}