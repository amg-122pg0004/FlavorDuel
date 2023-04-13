/*****************************************************************//**
 * \file   ChangeScreen.h
 * \brief  描画スクリーン(フレームバッファ)を変更する際、DXライブラリの仕様としてカメラ情報がリセットされてしまうため
 *         引き継ぐために作成したクラス
 * 
 * \author 土居将太郎
 * \date   February 2023
 *********************************************************************/
#pragma once
#include <DxLib.h>
namespace AppFrame {
    class ChangeScreen
    {
    public:
        struct CameraParam {
            MATRIX transform;
            float Near;
            float Far;
            float Fov;
        };
        /**
         * \brief 現在のカメラ情報を取得する
         * \return カメラ情報が入った構造体
         */
        static inline CameraParam GetCameraParam() { return { GetCameraViewMatrix(), GetCameraNear(), GetCameraFar(), GetCameraFov() }; }

        /**
         * \brief カメラ情報を設定する
         * \param param カメラ情報が入った構造体
         */
        static inline void SetCameraParam(CameraParam param) {
            SetCameraViewMatrix(param.transform);
            SetCameraNearFar(param.Near, param.Far);
            SetupCamera_Perspective(param.Fov);

        }
        /**
         * \brief カメラ情報を維持したまま描画スクリーンを切り替える
         * \param screen 変更する描画スクリーン
         */
        static void ChangeScreenAndSaveCamera(unsigned int screen);
    };

}