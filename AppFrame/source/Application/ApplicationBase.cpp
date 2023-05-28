/*****************************************************************//**
 * \file   ApplicationBase.h
 * \brief  アプリケーションの基底クラス
 * \brief  継承先のグローバル空間で実体を作成して使用する
 * \brief  Input,Update,Renderが順番にメインループで呼ばれる
 * \brief　Debugは継承先Render内で呼び出して使用する想定
 *
 * \author 土居将太郎
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

        // DXライブラリの初期化
        if (AppWindowed()) {
            ChangeWindowMode(true);							// ウィンドウモードに指定する
        }

        SetGraphMode(DispSizeW(), DispSizeH(), 32);
        SetAlwaysRunFlag(true);
        SetDoubleStartValidFlag(TRUE);
        if (DxLib_Init() == -1)
        {   // エラーが起きたら直ちに終了
            return false;
        }

        SetDrawScreen(DX_SCREEN_BACK);		// 描画先画面を裏画面にセット

        // 乱数初期化
        srand((unsigned int)time(NULL));

        // モードサーバの初期化
        _modeServer.reset(new ModeServer);
        //インプットマネージャーの初期化
        _inputManager.reset(new InputManager);
        _vibration.reset(new Vibration);
        _appData.reset(new DataHolder);

        return true;
    }

    bool ApplicationBase::Terminate() {
        // DXライブラリ開放
        DxLib_End();

        return true;
    }


    bool ApplicationBase::Input() {
        // キーの入力、トリガ入力を得る
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