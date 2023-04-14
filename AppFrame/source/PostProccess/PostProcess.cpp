#include "PostProcess.h"
#include "ApplicationBase.h"
#include "ChangeScreen.h"
#include "ModelServer.h"
#include "../CFile/CFile.h"

namespace {
	constexpr auto VertexShaderPath = "res/Shader/vertex_shader.vso";
	constexpr auto VertexShaderSkinMeshPath = "res/Shader/vertex_shader_skinmesh.vso";
	constexpr auto DepthToRedPath = "res/Shader/ZbufferRedPS.pso";
	constexpr auto DepthToGreenPath = "res/Shader/ZbufferGreenPS.pso";
	constexpr auto PPShaderPath = "res/Shader/PostProcessPS.pso";
	constexpr auto PPShaderNoBlurPath = "res/Shader/PostProcessNoBlurPS.pso";

	constexpr auto ModelPath = "res/Model/TestWall.mv1";

	constexpr auto SavePath = "res/SaveData/Blur.txt";

	constexpr int DownScale = 8;
}
namespace AppFrame {
	PostProcess::PostProcess() :_blur{ false }
	{
		auto app = ApplicationBase::GetInstance();
		_screenColor = MakeScreen(app->DispSizeW(), app->DispSizeH(), true);
		_backColor = MakeScreen(app->DispSizeW(), app->DispSizeH(), false);
		_ZBuffer = MakeScreen(app->DispSizeW(), app->DispSizeH(), false);
		_outputScreen = MakeScreen(app->DispSizeW(), app->DispSizeH(), true);
		_highBrightScreen = MakeScreen(app->DispSizeW(), app->DispSizeH(), false);
		_downScaleScreen = MakeScreen(app->DispSizeW() / DownScale, app->DispSizeH() / DownScale, false);

		_vertexShaderHandle = LoadVertexShader(VertexShaderPath);
		_vertexShaderHandleSkinMesh = LoadVertexShader(VertexShaderSkinMeshPath);
		_depthToRedPS = LoadPixelShader(DepthToRedPath);
		_depthToGreenPS = LoadPixelShader(DepthToGreenPath);
		_ppShaderHandle = LoadPixelShader(PPShaderPath);
		_ppShaderNoBlurHandle = LoadPixelShader(PPShaderNoBlurPath);

		_mv1Handle = ModelServer::LoadModel(ModelPath);
		MV1SetTextureGraphHandle(_mv1Handle, MV1GetMaterialDifMapTexture(_mv1Handle, 0), _backColor, true);
		MV1SetTextureGraphHandle(_mv1Handle, MV1GetMaterialNormalMapTexture(_mv1Handle, 0), _screenColor, true);
		MV1SetTextureGraphHandle(_mv1Handle, MV1GetMaterialSpcMapTexture(_mv1Handle, 0), _ZBuffer, true);
		MV1SetScale(_mv1Handle, { 1.78f,1.0f, 1.0f });
		MV1SetTextureAddressMode(_mv1Handle, 0, DX_TEXADDRESS_CLAMP, DX_TEXADDRESS_CLAMP);
		MV1SetTextureAddressMode(_mv1Handle, 1, DX_TEXADDRESS_CLAMP, DX_TEXADDRESS_CLAMP);
		MV1SetTextureAddressMode(_mv1Handle, 2, DX_TEXADDRESS_CLAMP, DX_TEXADDRESS_CLAMP);
	}

	PostProcess::~PostProcess()
	{
	}

	void PostProcess::DoProcessing(int renderScreen)
	{
		auto camera = ChangeScreen::GetCameraParam();
		auto app = ApplicationBase::GetInstance();
		SetDrawScreen(_outputScreen);
		SetupCamera_Ortho(20.0f);
		MV1SetUseZBuffer(_mv1Handle, FALSE);
		MV1SetWriteZBuffer(_mv1Handle, FALSE);
		SetCameraNearFar(100.0f, 200.0f);
		SetCameraPositionAndTarget_UpVecY({ 0.0f,0.0f,0.0f }, { 0.0f,00.0f,180.0f });
		MV1SetPosition(_mv1Handle, { 0.0f,0.0f,180.0f });
		SetUseLighting(false);
		SetUseVertexShader(_vertexShaderHandle);
		if (_blur) {
			SetUsePixelShader(_ppShaderHandle);
		}
		else {
			SetUsePixelShader(_ppShaderNoBlurHandle);
		}
		MV1SetUseOrigShader(true);
		MV1DrawModel(_mv1Handle);
		MV1SetUseOrigShader(false);
		SetUseLighting(true);
		ChangeScreen::SetCameraParam(camera);
		SetupCamera_Perspective(1.04272f);
		MV1SetUseZBuffer(_mv1Handle, TRUE);
		MV1SetWriteZBuffer(_mv1Handle, TRUE);

		ChangeScreen::ChangeScreenAndSaveCamera(renderScreen);
		DrawGraph(0, 0, _outputScreen, true);

		GraphFilterBlt(_outputScreen, _highBrightScreen, DX_GRAPH_FILTER_BRIGHT_CLIP, DX_CMP_LESS, 230, TRUE, GetColor(0, 0, 0), 255);
		GraphFilterBlt(_highBrightScreen, _downScaleScreen, DX_GRAPH_FILTER_DOWN_SCALE, DownScale);
		GraphFilter(_downScaleScreen, DX_GRAPH_FILTER_GAUSS, 16, 900);
		SetDrawMode(DX_DRAWMODE_BILINEAR);
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		DrawExtendGraph(0, 0, app->DispSizeW(), app->DispSizeH(), _downScaleScreen, false);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}

	void PostProcess::DontProcessing(int renderScreen)
	{
		ChangeScreen::ChangeScreenAndSaveCamera(renderScreen);
		DrawGraph(0, 0, _outputScreen, true);
	}

	void PostProcess::ClearAllScreen()
	{
		auto camera = ChangeScreen::GetCameraParam();
		SetDrawScreen(_backColor);
		ClearDrawScreen();
		SetDrawScreen(_ZBuffer);
		ClearDrawScreen();
		SetDrawScreen(_screenColor);
		ClearDrawScreen();
		SetDrawScreen(_outputScreen);
		ClearDrawScreen();
		ChangeScreen::SetCameraParam(camera);
	}

	void PostProcess::DrawNormal(int mv1Handle, bool skinMesh)
	{
		ChangeScreen::ChangeScreenAndSaveCamera(_backColor);
		MV1DrawModel(mv1Handle);

		ChangeScreen::ChangeScreenAndSaveCamera(_ZBuffer);
		if (skinMesh) {
			SetUseVertexShader(_vertexShaderHandleSkinMesh);
		}
		else {
			SetUseVertexShader(_vertexShaderHandle);
		}
		SetUsePixelShader(_depthToRedPS);
		MV1SetUseOrigShader(true);
		MV1DrawModel(mv1Handle);
		ChangeScreen::ChangeScreenAndSaveCamera(_outputScreen);
		MV1SetUseOrigShader(false);
	}

	void PostProcess::DrawPostProccess(int mv1Handle, bool skinMesh)
	{
		ChangeScreen::ChangeScreenAndSaveCamera(_screenColor);
		MV1DrawModel(mv1Handle);

		ChangeScreen::ChangeScreenAndSaveCamera(_ZBuffer);
		if (skinMesh) {
			SetUseVertexShader(_vertexShaderHandleSkinMesh);
		}
		else {
			SetUseVertexShader(_vertexShaderHandle);
		}

		SetUsePixelShader(_depthToGreenPS);
		MV1SetUseOrigShader(true);
		MV1DrawModel(mv1Handle);
		ChangeScreen::ChangeScreenAndSaveCamera(_outputScreen);
		MV1SetUseOrigShader(false);
	}

	void PostProcess::DrawNoProcessing(int mv1Handle)
	{
		MV1SetUseOrigShader(true);
		MV1DrawModel(mv1Handle);
		MV1SetUseOrigShader(false);
	}

	void PostProcess::DrawSphere3D(VECTOR CenterPos, float r, int DivNum, unsigned int DifColor, unsigned int SpcColor, int FillFlag)
	{
		ChangeScreen::ChangeScreenAndSaveCamera(_backColor);
		DxLib::DrawSphere3D(CenterPos, r, DivNum, DifColor, SpcColor, FillFlag);
		SetUseVertexShader(_vertexShaderHandle);
		SetUsePixelShader(_depthToRedPS);
		MV1SetUseOrigShader(true);
		ChangeScreen::ChangeScreenAndSaveCamera(_ZBuffer);
		DxLib::DrawSphere3D(CenterPos, r, DivNum, DifColor, SpcColor, FillFlag);
		ChangeScreen::ChangeScreenAndSaveCamera(_outputScreen);
		MV1SetUseOrigShader(false);
	}

	void PostProcess::Import()
	{
		CFile file(SavePath);
		std::string saveText = file.DataStr();
		if (saveText == "1") {
			_blur = true;
		}
	}
}