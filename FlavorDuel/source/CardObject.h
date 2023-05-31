/*****************************************************************//**
 * \file   CardObject.h
 * \brief  カードオブジェクト
 *
 * \author 土居将太郎
 * \date   May 2023
 *********************************************************************/
#pragma once
#include "appframe.h"
#include "CardDataStruct.h"
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

		void SetCardName(std::string name) { _data.name = name; }
		std::string GetCardName() { return _data.name; }

		void SetCardText(std::string text) { _data.flavorText = text; }
		std::string GetCardText() { return _data.flavorText; }

		void SetSelected(bool flag) { _selected = flag; }
		bool GetSelected() { return _selected; }

		void SetAttack(int attack) { _data.attack = attack; }
		int GetAttack() { return _data.attack; }

		void SetDefense(int defense) { _data.defence = defense; }
		int GetDefense() { return _data.defence; }

		void SetImage(int cg) { _cardCG = cg; }
		int GetImage() { return _cardCG; }

		int GetFrameImage() { return _frameCG; }

		void SetCardData(CardData data) { _data = data; }
		CardData GetCardData() { return _data; }

		int GetScreen() { return _screen; }
	private:
		CardData _data;
		int _frameCG;
		int _cardCG;
		bool _selected;
		AppFrame::AABB2D<int> _aabb;
		int _screen;
	};
}