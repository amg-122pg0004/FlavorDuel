/*****************************************************************//**
 * \file   ModeDeckEdit.h
 * \brief  デッキ編集画面
 *
 * \author 土居将太郎
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

		//ホーム画面に戻る
		void ChangeModeHome();

	private:
		std::unique_ptr<DeckEditThread> _thread;
		std::unique_ptr<CardObject> _editCard;
		std::vector<CardData> _cards;
		std::unique_ptr<CardFactory> _cardFactory;
		int _inputHandleName;//キー入力バッファ
		int _inputHandleText;//キー入力バッファ
		bool _inputActivateName, _inputActivateText;
	};
}
