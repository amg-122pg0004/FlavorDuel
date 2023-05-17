/*****************************************************************//**
 * \file   ModeMatching.h
 * \brief  �}�b�`���O���
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

	enum MatchType{ Casual,Rank };

	class ModeMatching : public AppFrame::ModeBase {
	public:
		ModeMatching(MatchType type);
		bool Initialize();
		bool Terminate();
		bool Update(InputManager& input);
		bool Render();
		bool Debug();

	private:

	};
}