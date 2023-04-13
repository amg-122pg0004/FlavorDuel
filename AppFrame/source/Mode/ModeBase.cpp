/*****************************************************************//**
 * \file   ModeBase.cpp
 * \brief  ���[�h�̊��N���X
 *
 * \author �y�������Y
 * \date   April 2023
 *********************************************************************/
#include "ModeBase.h"
#include "ObjectServer.h"
#include "BlurRenderer.h"
namespace AppFrame {


    ModeBase::ModeBase() {
        _szName = "";
        _uid = 1;
        _layer = 0;

        _cntMode = 0;
        _tmMode = 0;
        _tmStep = 0;
        _tmModeBase = 0;
        _tmPauseBase = 0;
        _tmPauseStep = 0;
        _tmOldFrame = 0;

        SetCallPerFrame(1);
        SetCallOfCount(1);

        _objectServer = nullptr;
        _blurRenderer = nullptr;
        _blurActivate = false;
    }

    ModeBase::~ModeBase() {
    }


    // ModeServer�ɐڑ����AProcess()�̑O�Ɉ�x�����Ă΂��
    bool	ModeBase::Initialize() {

        _objectServer.reset(new ObjectServer(*this));
        _blurRenderer.reset(new BlurRenderer);
        return true;
    }

    // ModeServer����폜�����ہA��x�����Ă΂��
    bool	ModeBase::Terminate() {

        return true;
    }


    // --------------------------------------------------------------------------
    /// @brief ���t���[���Ă΂��B���������L�q
    // --------------------------------------------------------------------------
    bool	ModeBase::Update(InputManager& input)
    {
        return	true;
    }

    // --------------------------------------------------------------------------
    /// @brief ���t���[���Ă΂��B�`�敔���L�q
    // --------------------------------------------------------------------------
    bool	ModeBase::Render()
    {
        _blurRenderer->ClearAllScreen();
        return	true;
    }

    bool	ModeBase::Debug()
    {
        return	true;
    }

    // ���Ԍo�߂�������
    void ModeBase::StepTime(unsigned long tmNow, float slowRate) {
        // ���Ԍo�ߏ���
        if (_cntMode == 0) {
            _tmMode = 0;
            _tmStep = 0;
            _tmModeBase = tmNow;
            _tmPauseBase = 0;
            _tmPauseStep = 0;
        }
        else {
            _tmMode = static_cast<unsigned int>((tmNow - _tmModeBase) * slowRate) + _tmPauseStep;
            _tmStep = static_cast<unsigned int>((tmNow - _tmOldFrame) * slowRate);
        }

        _tmOldFrame = tmNow;
    }

    // �J�E���g��i�߂�
    void ModeBase::StepCount() {
        _cntMode++;
    }
}