/*****************************************************************//**
 * \file   HomeUI.h
 * \brief  �z�[�����UI
 * 
 * \author �y�������Y
 * \date   May 2023
 *********************************************************************/
#pragma once
#include "appframe.h"
namespace Flavor {
	using AppFrame::InputManager;
	class HomeUI :public AppFrame::UICanvas
	{
	public:
		HomeUI();
		~HomeUI();
		void Init();
		void Terminate();
		void Update(InputManager& input, float deltaSeconds);
		void Render();
	};
}