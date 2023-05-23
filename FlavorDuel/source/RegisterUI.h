/*****************************************************************//**
 * \file   RegisterUI.h
 * \brief  ユーザー新規登録UI
 *
 * \author 土居将太郎
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
		TooShortID,//IDが短すぎる
		TooShortPassword,//パスワードが短すぎる
		ForbiddenCharacterID,//IDに使用禁止文字が含まれる
		ForbiddenCharacterPassword,//パスワードに使用禁止文字が含まれる
		DuplicateID,//重複ID
		PasswordNotMach//パスワードと再入力パスワードが一致しない
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
		 * \brief IDとパスワードに問題が無いか確認する
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
