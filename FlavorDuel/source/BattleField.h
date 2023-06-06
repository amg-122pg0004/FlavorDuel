/*****************************************************************//**
 * \file   BattleField.h
 * \brief  バトルフィールドのカード描画と
 *         ChatGPTによる能力値測定のため、データをポストする別スレッド作成
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
	class ModeInGame;
	class PostThread;
	class BattleField : public AppFrame::ObjectBase
	{
	public:
		BattleField(ModeInGame& mode);
		~BattleField();
		//オブジェクトサーバーに追加した際に呼ばれる
		virtual void Init();
		//オブジェクトサーバーから削除された際に呼ばれる
		virtual void Terminate();
		virtual void Update(InputManager& input);
		virtual void Render();
		virtual void Debug();

		void SetMyArea(CardData card);
		void SetOpponentArea(CardData card);
		void SetComfirm(bool flag) { _confirm = flag; }
	private:
		ModeInGame& _modeInGame;
		std::unique_ptr<CardObject> _myCard;
		std::unique_ptr<CardObject> _opponentCard;
		std::unique_ptr<PostThread> _threadHolder;
		int _font;
		int _fontSmall;
		float _judgeCompleteTimer;
		bool _confirm;
		int _myRandom, _opponentRandom;//能力値判定中に使用する乱数
		float _randomTimer;//乱数の再設定に使用するタイマー
	};
}