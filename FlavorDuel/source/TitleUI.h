/*****************************************************************//**
 * \file   TitleUI.cpp
 * \brief  �^�C�g����UI�L�����o�X
 *
 * \author �y�������Y
 * \date   May 2023
 *********************************************************************/
#pragma once
#include "appframe.h"

namespace Flavor {
	using AppFrame::InputManager;
	class ModeTitle;
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

	};
}
