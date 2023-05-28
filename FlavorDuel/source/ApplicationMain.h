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
		{{"ドラゴン","炎を吐く"},
		{"大きな亀","頑丈な甲羅にこもって暮らしている"},
		{"兵士","鎧を身に着け、大きな槍を持つ"},
		{"魔法使い","5属性の魔法を操る"},
		{"天使","雲の上に住む存在"},
		{"トレント","森に立ち入った人間を攻撃する"},
		{"僧侶","回復魔法を得意とする"},
		{"ゴブリン","ずる賢く、集団で行動する"},
		{"スライム","雨を吸収して生きている"},
		{"猫","鳴き声は「にゃーん」"}}
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