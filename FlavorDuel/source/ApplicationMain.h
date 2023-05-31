/*****************************************************************//**
 * \file   ApplicationMain.h
 * \brief  WinMainから呼ばれるクラス
 * 
 * \author 土居将太郎
 * \date   May 2023
 *********************************************************************/
#pragma once
#include "appframe.h"
#include "CardDataStruct.h"
namespace {
	std::vector<Flavor::CardData> TestDeck = {
		{{"悪魔","邪悪な心をもっている",0},
		{"ドラゴン","炎を吐き、街を燃やす",1},
		{"大きな亀","固い甲羅で身を守っている",2},
		{"ゴブリン","ずる賢く、集団で行動するあああああああああああああ",3},
		{"騎士","正義を重んじる騎士",4},
		{"メカカマキリ","その巨大な鎌はどんな盾も切断可能あああああああ",5},
		{"悪の羊","夢に出てくると不吉なことが起きるらしい",6},
		{"スライム","雨を吸収して生きている",7},
		{"トレント","通りがかった人に噛みつく木",8},
		{"魔法使い","5属性の魔法を操る",9}}
	};
}
namespace Flavor {
	class ApplicationMain :public AppFrame::ApplicationBase
	{
	public:
		ApplicationMain();
		bool Initialize(HINSTANCE hInstance);
		bool Input();
		bool Update();
		bool Render();
		bool Debug();
		virtual int DispSizeW() { return 1280; }
		virtual int DispSizeH() { return 720; }
	private:
		bool _debug;
	};
}