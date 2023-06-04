/*****************************************************************//**
 * \file   InGameUI.h
 * \brief  インゲームUI 勝利数表示
 * 
 * \author 土居将太郎
 * \date   May 2023
 *********************************************************************/
#pragma once
#include "appframe.h"
namespace Flavor {
	using AppFrame::InputManager;
	class ModeInGame;
	class InGameUI :public AppFrame::UICanvas
	{
	public:
		InGameUI(ModeInGame& mode);
		~InGameUI();
		void Init();
		void Terminate();
		void Update(InputManager& input, float deltaSeconds);
		void Render();
	private:
		ModeInGame& _modeInGame;
	};
}