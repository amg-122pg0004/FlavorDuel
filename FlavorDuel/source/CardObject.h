/*****************************************************************//**
 * \file   CardObject.h
 * \brief  カードオブジェクト
 * 
 * \author 土居将太郎
 * \date   May 2023
 *********************************************************************/
#pragma once
#include "appframe.h"
namespace Flavor {
	using AppFrame::InputManager;
	class CardObject;
	class CardObject : public AppFrame::ObjectBase
	{
	public:
		CardObject();
		~CardObject();
		void Init()override;
		void Terminate()override;
		void Update(InputManager& input)override;
		void Render()override;
		void Debug()override;

		void SetCardName(std::string name) { _cardName = name; }
		std::string GetCardName() { return _cardName ; }
		void SetCardText(std::string text) { _cardText = text; }
		std::string GetCardText() { return _cardText; }
		void SetSelected(bool flag) { _selected = flag; }
		bool GetSelected() { return _selected; }
		int GetCGHandle() { return _cg; }

		void SetAttack(int attack) { _attack = attack; }
		int GetAttack() { return _attack; }
		void SetDefense(int defense) { _defense = defense; }
		int GetDefense() { return _defense; }
		void SetTips(std::string tips) { _tips = tips; }
		std::string GetTips() { return _tips; }
	private:
		int _cg;
		std::string _cardName;
		std::string _cardText;
		int _attack,_defense;
		std::string _tips;
		bool _selected;
		AppFrame::AABB2D<int> _aabb;
	};
}