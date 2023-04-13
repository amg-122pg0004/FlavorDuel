/*****************************************************************//**
 * \file   WinMain.cpp
 * \brief  エントリーポイント
 *
 * \author 土居将太郎
 * \date   December 2022
 *********************************************************************/
#include "appframe.h"
int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow
) {
    AppFrame::ApplicationBase* appBase = AppFrame::ApplicationBase::GetInstance();

    if (!appBase) { return 0; }

    if (!appBase->Initialize(hInstance)) {
        return 0;
    }

    while (ProcessMessage() == 0)
    {
        appBase->Input();
        appBase->Update();
        appBase->Render();
        ScreenFlip();

        if (appBase->GetAppEnd()) {
            break;
        }
    }

    appBase->Terminate();

    return 0;
}