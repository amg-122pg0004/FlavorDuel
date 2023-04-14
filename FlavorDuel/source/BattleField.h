#pragma once
#include "appframe.h"
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

		void SetMyArea(CardObject* card) { _myCard = card; }
		void SetEnemyArea(CardObject* card) { _opponentCard = card; }
	private:
		bool _settMyCard, _setOpponentCard;
		ModeInGame& _modeInGame;
		CardObject* _myCard;
		CardObject* _opponentCard;
		std::unique_ptr<PostThread> _threadHolder;
		int _font;
	};
}