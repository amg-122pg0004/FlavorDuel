/*****************************************************************//**
 * \file   ModeDeckEdit.h
 * \brief  �f�b�L�ҏW���
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
