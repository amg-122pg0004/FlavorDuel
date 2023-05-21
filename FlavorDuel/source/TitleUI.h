/*****************************************************************//**
 * \file   TitleUI.cpp
 * \brief  タイトルのUIキャンバス
 *
 * \author 土居将太郎
 * \date   May 2023
 *********************************************************************/
#pragma once
#include "appframe.h"
#include "UserDataStruct.h"

namespace Flavor {
	using AppFrame::InputManager;
	class ModeTitle;
	class LoginThread;
	enum class LoginState{ Idle,Success,Fail };

	class TitleUI : public AppFrame::UICanvas
	{
	public:
		TitleUI(ModeTitle& mode);
		~TitleUI();
		void Init();
		void Terminate();
		void Update(InputManager& input, float deltaSeconds);
		void Render();
	private:
		std::unique_ptr<LoginThread> _loginThread;
		AppFrame::UI::EditableTextBox* _name;
		AppFrame::UI::EditableTextBox* _password;
		LoginState _loginState;
		UserData _data;
	};
}
