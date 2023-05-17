
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

		int _screenColor;//�u���[���p
		int _backColor;//�ʏ�`��p
		int _ZBuffer;//�ʏ�`��p

		int _vertexShaderHandle;//�ʏ�
		int _vertexShaderHandleSkinMesh;//�X�L�����b�V���p
		int _depthToRedPS;//�[�x���J���[�ϊ��p�V�F�[�_�[
		int _depthToGreenPS;//�[�x���J���[�ϊ��p�V�F�[�_�[
		int _ppShaderHandle;
		int _ppShaderNoBlurHandle;

		bool _blur;
		void Import();
		int _outputScreen;
		int _highBrightScreen;
		int _downScaleScreen;
	};
}