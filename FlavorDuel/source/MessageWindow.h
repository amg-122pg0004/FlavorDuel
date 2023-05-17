/*****************************************************************//**
 * \file   MessageWindow.h
 * \brief  インゲーム画面右部に表示されるメッセージ1個分
 *         MessageLogの子として追加されていく
 * 
 * \author 土居将太郎
 * \date   May 2023
 *********************************************************************/
#pragma once
#include "appframe.h"
namespace Flavor {
	using AppFrame::InputManager;
	class MessageWindow :public AppFrame::UICanvas
	{
	public:
		MessageWindow(std::string message);
		void Init();
		void Terminate();
		void Update(InputManager& input, float deltaSeconds);
		void Render();
	private:
	};
}
