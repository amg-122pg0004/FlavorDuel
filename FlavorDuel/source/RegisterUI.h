/*****************************************************************//**
 * \file   RegisterUI.h
 * \brief  ���[�U�[�V�K�o�^UI
 *
 * \author �y�������Y
 * \date   May 2023
 *********************************************************************/
#pragma once
#include <appframe.h>

namespace Flavor {
	using AppFrame::InputManager;
	class ModeTitle;
	class RegisterThread;
	enum class RegisterError { 
		None,
		TooShortID,//ID���Z������
		TooShortPassword,//�p�X���[�h���Z������
		ForbiddenCharacterID,//ID�Ɏg�p�֎~�������܂܂��
		ForbiddenCharacterPassword,//�p�X���[�h�Ɏg�p�֎~�������܂܂��
		DuplicateID,//�d��ID
		PasswordNotMach//�p�X���[�h�ƍē��̓p�X���[�h����v���Ȃ�
	};

	class RegisterUI : public AppFrame::UICanvas
	{
	public:
		RegisterUI(ModeTitle& mode);
		void Init();
		void Terminate();
		void Update(InputManager& input, float deltaSeconds);
		void Render();
	private:
		/**
		 * \brief ID�ƃp�X���[�h�ɖ�肪�������m�F����
		 */
		void CheckIDAndPassword();
		ModeTitle& _titleMode;
		std::unique_ptr<RegisterThread> _registerThread;
		RegisterError _error;
		AppFrame::UI::EditableTextBox* _name;
		AppFrame::UI::EditableTextBox* _password;
		AppFrame::UI::EditableTextBox* _passwordReenter;
		AppFrame::UI::TextBox* _errorText;
	};
}
