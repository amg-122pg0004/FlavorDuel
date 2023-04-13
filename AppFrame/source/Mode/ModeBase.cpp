/*****************************************************************//**
 * \file   ModeBase.cpp
 * \brief  モードの基底クラス
 *
 * \author 土居将太郎
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


    // ModeServerに接続時、Process()の前に一度だけ呼ばれる
    bool	ModeBase::Initialize() {

        _objectServer.reset(new ObjectServer(*this));
        _blurRenderer.reset(new BlurRenderer);
        return true;
    }

    // ModeServerから削除される際、一度だけ呼ばれる
    bool	ModeBase::Terminate() {

        return true;
    }


    // --------------------------------------------------------------------------
    /// @brief 毎フレーム呼ばれる。処理部を記述
    // --------------------------------------------------------------------------
    bool	ModeBase::Update(InputManager& input)
    {
        return	true;
    }

    // --------------------------------------------------------------------------
    /// @brief 毎フレーム呼ばれる。描画部を記述
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

    // 時間経過をさせる
    void ModeBase::StepTime(unsigned long tmNow, float slowRate) {
        // 時間経過処理
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

    // カウントを進める
    void ModeBase::StepCount() {
        _cntMode++;
    }
}