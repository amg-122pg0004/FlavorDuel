
#pragma once
#include <DxLib.h>
#include <memory>
namespace AppFrame {
	class PostProcess
	{
	public:
		PostProcess();
		~PostProcess();
		void DoProcessing(int renderScreen);
		void DontProcessing(int renderScreen);

		void ClearAllScreen();
		void SetOutputScreen(unsigned int output) { _outputScreen = output; }
		unsigned int GetOutputScreen() { return _outputScreen; }

		void DrawNormal(int mv1Handle, bool skinMesh = false);
		void DrawPostProccess(int mv1Handle, bool skinMesh = false);
		void DrawNoProcessing(int mv1Handle);
		void DrawSphere3D(VECTOR CenterPos, float r, int DivNum, unsigned int DifColor, unsigned int SpcColor, int FillFlag);
	private:

		int _mv1Handle;

		int _screenColor;//ブルーム用
		int _backColor;//通常描画用
		int _ZBuffer;//通常描画用

		int _vertexShaderHandle;//通常
		int _vertexShaderHandleSkinMesh;//スキンメッシュ用
		int _depthToRedPS;//深度→カラー変換用シェーダー
		int _depthToGreenPS;//深度→カラー変換用シェーダー
		int _ppShaderHandle;
		int _ppShaderNoBlurHandle;

		bool _blur;
		void Import();
		int _outputScreen;
		int _highBrightScreen;
		int _downScaleScreen;
	};
}