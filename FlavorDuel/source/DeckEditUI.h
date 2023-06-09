/*****************************************************************//**
 * \file   DeckEditUI.h
 * \brief  fbLÒWæÊUI
 * 
 * \author y«¾Y
 * \date   June 2023
 *********************************************************************/
#pragma once
#include "appframe.h"
namespace Flavor {
	using AppFrame::InputManager;
	class ModeDeckEdit;
	class DeckEditUI :public AppFrame::UICanvas
	{
	public:
		DeckEditUI(ModeDeckEdit& mode);
		~DeckEditUI();
		void Init();
		void Terminate();
		void Update(InputManager& input, float deltaSeconds);
		void Render();
	private:
		ModeDeckEdit& _mode;
		int _cardListScrollIndex;
	};
}