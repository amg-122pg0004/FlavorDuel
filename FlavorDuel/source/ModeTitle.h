/*****************************************************************//**
 * \file   ModeTitle.h
 * \brief  �^�C�g����ʁA���O�C�����邢�̓��[�U�[�o�^���ăz�[����ʂɑJ��
 * 
 * \author �y�������Y
 * \date   May 2023
 *********************************************************************/
#pragma once
#include "appframe.h"
namespace Flavor {
	using AppFrame::InputManager;
	class CardFactory;
	class MessageLog;

	class ModeTitle : public AppFrame::ModeBase {
	public:
		ModeTitle();
		bool Initialize();
		bool Terminate();
		bool Update(InputManager& input);
		bool Render();
		bool Debug();

		void Login(std::string userName, std::string password);
		void Register(std::string userName, std::string password);
		void QuitGame();
	private:

	};
}

