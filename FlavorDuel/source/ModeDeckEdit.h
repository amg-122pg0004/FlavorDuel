/*****************************************************************//**
 * \file   ModeDeckEdit.h
 * \brief  デッキ編集画面
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

	class ModeDeckEdit : public AppFrame::ModeBase {
	public:
		ModeDeckEdit();
		bool Initialize();
		bool Terminate();
		bool Update(InputManager& input);
		bool Render();
		bool Debug();

	private:

	};
}
