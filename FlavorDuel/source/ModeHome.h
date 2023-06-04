/*****************************************************************//**
 * \file   ModeHome.h
 * \brief  ホーム画面モード
 * 
 * \author 土居将太郎
 * \date   May 2023
 *********************************************************************/
#pragma once
#include "appframe.h"
namespace Flavor {
	using AppFrame::InputManager;
	class ModeHome :public AppFrame::ModeBase {
	public:
		ModeHome();
		bool Initialize();
		bool Terminate();
		bool Update(InputManager& input);
		bool Render();
		bool Debug();

		//マッチングモードを作成する
		void OpenMatching();
		//デッキ編集モードに移動する
		void ChangeModeDeckEdit();
	private:
	};
}