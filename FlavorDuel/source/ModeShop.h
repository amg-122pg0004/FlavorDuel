/*****************************************************************//**
 * \file   ModeShop.h
 * \brief  �V���b�v��ʁ@�J�[�h�p�b�N��������
 * 
 * \author �y�������Y
 * \date   May 2023
 *********************************************************************/

#pragma once
#include "appframe.h"
#include "CardDataStruct.h"
namespace Flavor {
	using AppFrame::InputManager;
	class CardFactory;
	class MessageLog;

	class ModeShop : public AppFrame::ModeBase {
	public:
		ModeShop();
		bool Initialize();
		bool Terminate();
		bool Update(InputManager& input);
		bool Render();
		bool Debug();

		std::array<CardData,5> BuyPack(int packNumber);
	private:

	};
}
