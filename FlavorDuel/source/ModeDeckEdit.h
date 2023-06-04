/*****************************************************************//**
 * \file   ModeDeckEdit.h
 * \brief  �f�b�L�ҏW���
 *
 * \author �y�������Y
 * \date   May 2023
 *********************************************************************/
#pragma once
#include "appframe.h"
#include "CardDataStruct.h"
#include "DeckEditThread.h"
namespace Flavor {
	using AppFrame::InputManager;
	class CardObject;
	class CardFactory;
	class ModeDeckEdit : public AppFrame::ModeBase {
	public:
		ModeDeckEdit();
		bool Initialize();
		bool Terminate();
		bool Update(InputManager& input);
		bool Render();
		bool Debug();

		void SetEditCard(CardData data);
		std::unique_ptr<CardObject>& GetEditCard() { return _editCard; }

		void ApplyEditData();

		std::vector<CardData> GetCards() { return _cards; }
		std::unique_ptr<CardFactory>& GetCardFactory() { return _cardFactory; }

		//�z�[����ʂɖ߂�
		void ChangeModeHome();

	private:
		std::unique_ptr<DeckEditThread> _thread;
		std::unique_ptr<CardObject> _editCard;
		std::vector<CardData> _cards;
		std::unique_ptr<CardFactory> _cardFactory;
		int _inputHandleName;//�L�[���̓o�b�t�@
		int _inputHandleText;//�L�[���̓o�b�t�@
		bool _inputActivateName, _inputActivateText;
	};
}
