/*****************************************************************//**
 * \file   ModeTitle.h
 * \brief  タイトル画面、ログインあるいはユーザー登録してホーム画面に遷移
 *
 * \author 土居将太郎
 * \date   May 2023
 *********************************************************************/
#pragma once
#include "appframe.h"
namespace Flavor {
	using AppFrame::InputManager;
	class CardFactory;
	class MessageLog;
	enum class TitleUI { Login, Register };
	class ModeTitle : public AppFrame::ModeBase {
	public:
		ModeTitle();
		bool Initialize();
		bool Terminate();
		bool Update(InputManager& input);
		bool Render();
		bool Debug();

		void SetNextUI(TitleUI ui) { _nextUI = ui; _changeFlag = true; }
		void ChangeModeHome();
	private:
		void ChangeUI();
		bool _changeFlag;
		TitleUI _nextUI;
	};
}

