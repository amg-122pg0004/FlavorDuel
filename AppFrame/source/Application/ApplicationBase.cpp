/*****************************************************************//**
 * \file   ApplicationBase.h
 * \brief  �A�v���P�[�V�����̊��N���X
 * \brief  �p����̃O���[�o����ԂŎ��̂��쐬���Ďg�p����
 * \brief  Input,Update,Render�����ԂɃ��C�����[�v�ŌĂ΂��
 * \brief�@Debug�͌p����Render���ŌĂяo���Ďg�p����z��
 *
 * \author �y�������Y
 * \date   December 2022
 *********************************************************************/
#include "ApplicationBase.h"
#include "ModeServer.h"
#include "InputManager.h"
#include "Vibration.h"
#include "SoundServer.h"

namespace AppFrame {

    ApplicationBase* ApplicationBase::_lpInstance = NULL;


    ApplicationBase::ApplicationBase() {
        _lpInstance = this;
        _modeServer = nullptr;
        _inputManager = nullptr;
        _appEnd = false;
        _appData = nullptr;
    }

    ApplicationBase::~ApplicationBase() {
    }

    bool ApplicationBase::Initialize(HINSTANCE hInstance) {
        SetOutApplicationLogValidFlag(FALSE);
        SetZBufferBitDepth(64);

        // DX���C�u�����̏�����
        if (AppWindowed()) {
            ChangeWindowMode(true);							// �E�B���h�E���[�h�Ɏw�肷��
        }

        SetGraphMode(DispSizeW(), DispSizeH(), 32);
        SetAlwaysRunFlag(true);
        SetDoubleStartValidFlag(TRUE);
        if (DxLib_Init() == -1)
        {   // �G���[���N�����璼���ɏI��
            return false;
        }

        SetDrawScreen(DX_SCREEN_BACK);		// �`����ʂ𗠉�ʂɃZ�b�g

        // ����������
        srand((unsigned int)time(NULL));

        // ���[�h�T�[�o�̏�����
        _modeServer.reset(new ModeServer);
        //�C���v�b�g�}�l�[�W���[�̏�����
        _inputManager.reset(new InputManager);
        _vibration.reset(new Vibration);
        _appData.reset(new DataHolder);

        return true;
    }

    bool ApplicationBase::Terminate() {
        // DX���C�u�����J��
        DxLib_End();

        return true;
    }


    bool ApplicationBase::Input() {
        // �L�[�̓��́A�g���K���͂𓾂�
        _inputManager->Input();
        return true;
    }

    bool ApplicationBase::Update() {
        SoundServer::CheckLoad();
        _modeServer->UpdateInit();
        _modeServer->Update(*_inputManager);
        _modeServer->UpdateFinish();
        return true;
    }

    bool ApplicationBase::Render() {
        ClearDrawScreen();
        _modeServer->RenderInit();
        _modeServer->Render();
        _modeServer->RenderFinish();
        return true;
    }

    bool ApplicationBase::Debug()
    {
        _modeServer->DebugInit();
        _modeServer->Debug();
        _modeServer->DebugFinish();

        return true;
    }
}