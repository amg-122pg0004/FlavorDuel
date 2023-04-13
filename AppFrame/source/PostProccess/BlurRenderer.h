/*****************************************************************//**
 * \file   BlurRenderer.h
 * \brief  3Dオブジェクトにブラーを掛ける機能を持つクラス
 *         DrawBlurBufferからブラーを加えたいモデルを、DrawNotBlurBufferから加えたくないモデルをスクリーンバッファに描画する
 *         ApplyBlurかNotApplyBlurで通常の画面描画に使用されるスクリーン(_outputScreen)に戻します
 *
 * \author 土居将太郎
 * \date   March 2023
 *********************************************************************/
#pragma once
#include <DxLib.h>
#include <memory>
namespace AppFrame {
    class BlurRenderer
    {
    public:
        BlurRenderer();
        ~BlurRenderer();
        void ApplyBlur(int renderScreen);
        void NotApplyBlur(int renderScreen);

        void ClearAllScreen();
        void SetOutputScreen(unsigned int output) { DeleteGraph(_outputScreen), _outputScreen = output; }
        unsigned int GetOutputScreen() { return _outputScreen; }

        void DrawNotBlurBuffer(int mv1Handle, bool skinMesh = false);
        void DrawBlurBuffer(int mv1Handle, bool skinMesh = false);
        void DrawSphere3D(VECTOR CenterPos, float r, int DivNum, unsigned int DifColor, unsigned int SpcColor, int FillFlag);
    private:

        int _renderModel;//板モデル テクスチャに_screenColor、_backColor、_ZBufferを設定して再描画することでシェーダーを通す
        //ブラー用スクリーンハンドル
        int _screenColor;//ブラーオブジェクト用描画
        int _backColor;//ブラー無しオブジェクト描画用
        int _ZBuffer;//ブラーオブジェクトは赤、ブラー無しオブジェクトは緑に深度を書き込む

        int _outputScreen;//描画用スクリーン
        int _highBrightScreen;//ブルーム用、高輝度ピクセル抽出スクリーン
        int _downScaleScreen;//ブルーム用、高輝度ピクセルぼかしスクリーン

        //シェーダーハンドル
        int _vertexShaderHandle;//アニメーションしないモデル用
        int _vertexShaderHandleSkinMesh;//スキンメッシュモデル用
        int _depthToRedPS;//深度→赤変換用シェーダー
        int _depthToGreenPS;//深度→緑変換用シェーダー
        int _ppShaderHandle;//ブラー用シェーダー
        int _ppShaderNoBlurHandle;//ブラーを使用しないシェーダー

        bool _blur;
        void Import();

    };
}