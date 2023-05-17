/*****************************************************************//**
 * \file   ModeServer.h
 * \brief  ���[�h���Ǘ�����N���X
 *         �v���O�����̓��[�h�P�ʂŕ�����Ă���i�^�C�g�����[�h�A�X�e�[�W�I�����[�h�A�C���Q�[�����[�h���j
 *         �����̃��[�h�������Ă���Ƃ��A���C���[����̕���D�悵�ĕ`�悷��
 * 
 * \author �y�������Y
 * \date   December 2022
 *********************************************************************/
#pragma once
#include <memory>
#include <vector>
#include <algorithm>
#include <map>
#include "ModeBase.h"
namespace AppFrame {


    class InputManager;
    class	ModeServer
    {
    public:
        ModeServer();
        virtual	~ModeServer();
        static ModeServer* GetInstance() { return _lpInstance; }

        int Add(std::unique_ptr<ModeBase> mode);		// �o�^�͂��邪�A��x���C�����񂳂Ȃ��Ƃ����Ȃ�
        int Del(ModeBase* mode, int delayFrame = 0);		// �폜�\��
        ModeBase* Get(int uid);
        ModeBase* Get(const std::string name);
        int GetId(ModeBase* mode);
        int GetId(const std::string);
        const std::string GetName(ModeBase* mode);
        const std::string GetName(int uid);
        void Clear();
        int	LayerTop() { return INT32_MAX; }

        int UpdateInit();	// �v���Z�X���񂷂��߂̏�����
        int Update(InputManager& input);		// ���C���[�̏�̕����珈��
        int UpdateFinish();		// �v���Z�X���񂵂���̌�n��

        int RenderInit();		// �`����񂷂��߂̏�����
        int Render();		// ���C���[�̉��̕����珈��
        int RenderFinish();		// �`����񂵂���̌�n��

        int DebugInit();		// �f�o�b�O���񂷂��߂̏�����
        int Debug();		// ���C���[�̉��̕����珈��
        int DebugFinish();		// �f�o�b�O���񂵂���̌�n��

        int SkipUpdateUnderLayer();		// ��Process�ŁA���������Ă��郌�C���[��艺�̃��C���[�́A�������Ă΂Ȃ�
        int SkipRenderUnderLayer();			// ��Process�ŁA���������Ă��郌�C���[��艺�̃��C���[�́A�`����Ă΂Ȃ�
        int PauseProcessUnderLayer();		// ��Process�ŁA���������Ă��郌�C���[��艺�̃��C���[�́A���Ԍo�߂��~�߂�

        float GetSlowRate() { return _slowRate; }
        void SetSlow(float rate, float duration);

    private:
        int Release(ModeBase* mode);		// �폜��delete
        bool IsDelRegist(ModeBase* mode);	// �폜�\�񂳂�Ă��邩�H
        bool IsAdd(ModeBase* mode);		// ���X�g�ɂ��邩�H
        static ModeServer* _lpInstance;

        std::vector<std::unique_ptr<ModeBase>>	_vMode;			// ���[�h���X�g
        std::vector<std::unique_ptr<ModeBase>>	_vModeAdd;		// �ǉ��\��
        std::vector<ModeBase*>	_vModeDel;		// �폜�\��
        std::map<ModeBase*, int> _deleteDelay;//�폜�\��^�C�}�[ �l��1�����炵��0�ɂȂ�����폜

        ModeBase* _nowMode;		// ���݌Ăяo�����̃��[�h
        ModeBase* _skipUpdateMode;	// ���̃��[�h��艺��Process���Ă΂Ȃ�
        ModeBase* _skipRenderMode;	// ���̃��[�h��艺��Render���Ă΂Ȃ�
        ModeBase* _pauseUpdateMode;	// ���̃��[�h��艺��Process���Ɏ��Ԍo�߂������Ȃ�

        int	_uid_count;		// uid�J�E���^
        float _slowRate;
        unsigned int _slowStart;
        float _slowDuration;
    };
}
