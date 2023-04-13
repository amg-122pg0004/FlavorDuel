/*****************************************************************//**
 * \file   ApplicationBase.h
 * \brief  アプリケーションの基底クラス
 *         継承先のグローバル空間で実体を作成して使用する
 *         Input,Update,Renderが順番にメインループで呼ばれる
 *       　Debugは継承先Render内で呼び出して使用する想定
 * 
 * \author 土居将太郎
 * \date   December 2022
 *********************************************************************/

#include "dxlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory>

namespace AppFrame {
    class ModeServer;
    class InputManager;
    class Vibration;

    class ApplicationBase
    {
    public:
        ApplicationBase();
        virtual ~ApplicationBase();

        virtual bool Initialize(HINSTANCE hInstance);
        virtual bool Terminate();
        virtual bool Input();
        virtual bool Update();
        virtual bool Render();
        virtual bool Debug();

        virtual bool AppWindowed() { return true; }
        virtual int DispSizeW() { return 640; }
        virtual int DispSizeH() { return 480; }

        static	ApplicationBase* GetInstance() { return _lpInstance; }

        virtual bool GetAppEnd() { return _appEnd; }
        virtual void SetAppEnd(bool flag) { _appEnd = flag; }
    private:
        static	ApplicationBase* _lpInstance;//継承先でthisポインタが入る
        std::unique_ptr<ModeServer> _modeServer;//モード管理クラス
        std::unique_ptr<Vibration> _vibration;//振動のオンオフ管理
        bool _appEnd;//ゲーム終了hフラグ
    protected:
        std::unique_ptr<InputManager> _inputManager;//入力を取得
    };
}
