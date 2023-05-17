/*****************************************************************//**
 * \file   MessageLog.cpp
 * \brief  インゲーム画面右部に表示されるメッセージ表示枠
 *         子としてMessageWindowが追加されるのでそれらを管理する
 *
 * \author 土居将太郎
 * \date   May 2023
 *********************************************************************/
#pragma once
#include "appframe.h"
namespace Flavor {
	using AppFrame::InputManager;
	class MessageLog: public AppFrame::UICanvas
	{
	public:
		MessageLog();
		void Init();
		void Terminate();
		void Update(InputManager& input, float deltaSeconds);
		void Render();
	};
}