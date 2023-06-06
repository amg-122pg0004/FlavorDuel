/*****************************************************************//**
 * \file   BattleField.h
 * \brief  �o�g���t�B�[���h�̃J�[�h�`���
 *         ChatGPT�ɂ��\�͒l����̂��߁A�f�[�^���|�X�g����ʃX���b�h�쐬
 *
 * \author �y�������Y
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
		//�I�u�W�F�N�g�T�[�o�[�ɒǉ������ۂɌĂ΂��
		virtual void Init();
		//�I�u�W�F�N�g�T�[�o�[����폜���ꂽ�ۂɌĂ΂��
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
		int _myRandom, _opponentRandom;//�\�͒l���蒆�Ɏg�p���闐��
		float _randomTimer;//�����̍Đݒ�Ɏg�p����^�C�}�[
	};
}