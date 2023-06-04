/*****************************************************************//**
 * \file   MatchingUI.h
 * \brief  �}�b�`���O�L�����Z���{�^����\������UI�L�����o�X
 * 
 * \author �y�������Y
 * \date   May 2023
 *********************************************************************/
#pragma once
#include "appframe.h"
namespace Flavor {
	using AppFrame::InputManager;
	class ModeMatching;
	class MatchingUI :public AppFrame::UICanvas
	{
	public:
		MatchingUI(ModeMatching& mode);
		~MatchingUI();
		void Init();
		void Terminate();
		void Update(InputManager& input, float deltaSeconds);
		void Render();
	private:
		ModeMatching& _mode;
	};
}