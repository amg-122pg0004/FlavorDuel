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
            EditableTextBox(std::string text, int maxStrLength, int cancelValidFlag, int singleCharOnlyFlag, int numCharOnlyFlag);
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

            /**
             * \brief ��\�����[�h(��������������)��ݒ肷��
             * \param flag �I���I�t
             */
            void SetSecret(bool flag) { _secret = flag; }
            bool GetSecret() { return _secret; }

            std::string GetText() { return _text; }

            void SetDefaultText(std::string text) { _defaultText = text; }
            void SetTextColor(unsigned int color) { _textColor = color; }
        private:
            std::string _defaultText;//���͂������ꍇ�̕\���e�L�X�g
            std::string _text;
            int _font;
            unsigned int _defaultTextColor;
            unsigned int _textColor;
            bool _drawBox;//�����̔w�i�{�b�N�X��`�悷�邩
            unsigned int _boxColor;

            int _inputHandle;//�L�[���̓o�b�t�@
            bool _activate;//���͎�t��
            bool _secret;//�������[�h
        };
    }
}