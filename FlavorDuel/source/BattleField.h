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
		//�I�u�W�F�N�g�T�[�o�[�ɒǉ������ۂɌĂ΂��
		virtual void Init();
		//�I�u�W�F�N�g�T�[�o�[����폜���ꂽ�ۂɌĂ΂��
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