/*****************************************************************//**
 * \file   LoginUI.cpp
 * \brief  タイトル、ログイン画面のUIキャンバス
 *
 * \author 土居将太郎
 * \date   May 2023
 *********************************************************************/
#pragma once
#include "appframe.h"

namespace Flavor {
	using AppFrame::InputManager;
	class ModeTitle;
	class LoginThread;
	enum class LoginState{ Idle,Success,Fail };
	class LoginUI : public AppFrame::UICanvas
	{
	public:
		LoginUI(ModeTitle& mode);
		~LoginUI();
		void Init();
		void Terminate();
		void Update(InputManager& input, float deltaSeconds);
		void Render();
	private:
		ModeTitle& _titleMode;
		std::unique_ptr<LoginThread> _loginThread;
		AppFrame::UI::EditableTextBox* _name;
		AppFrame::UI::EditableTextBox* _password;
		LoginState _loginState;
	};
}
