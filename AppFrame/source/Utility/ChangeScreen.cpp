/*****************************************************************//**
 * \file   ChangeScreen.cpp
 * \brief  描画スクリーン(フレームバッファ)を変更する際、DXライブラリの仕様としてカメラ情報がリセットされてしまうため
 *         引き継ぐために作成したクラス
 *
 * \author 土居将太郎
 * \date   February 2023
 *********************************************************************/
#include "ChangeScreen.h"
namespace AppFrame {
    void ChangeScreen::ChangeScreenAndSaveCamera(unsigned int screen)
    {
        auto camera = GetCameraParam();
        SetDrawScreen(screen);
        SetCameraParam(camera);
        return;
    }
}