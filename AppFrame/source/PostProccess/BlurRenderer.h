/*****************************************************************//**
 * \file   BlurRenderer.h
 * \brief  3D�I�u�W�F�N�g�Ƀu���[���|����@�\�����N���X
 *         DrawBlurBuffer����u���[�������������f�����ADrawNotBlurBuffer������������Ȃ����f�����X�N���[���o�b�t�@�ɕ`�悷��
 *         ApplyBlur��NotApplyBlur�Œʏ�̉�ʕ`��Ɏg�p�����X�N���[��(_outputScreen)�ɖ߂��܂�
 *
 * \author �y�������Y
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

        int _renderModel;//���f�� �e�N�X�`����_screenColor�A_backColor�A_ZBuffer��ݒ肵�čĕ`�悷�邱�ƂŃV�F�[�_�[��ʂ�
        //�u���[�p�X�N���[���n���h��
        int _screenColor;//�u���[�I�u�W�F�N�g�p�`��
        int _backColor;//�u���[�����I�u�W�F�N�g�`��p
        int _ZBuffer;//�u���[�I�u�W�F�N�g�͐ԁA�u���[�����I�u�W�F�N�g�͗΂ɐ[�x����������

        int _outputScreen;//�`��p�X�N���[��
        int _highBrightScreen;//�u���[���p�A���P�x�s�N�Z�����o�X�N���[��
        int _downScaleScreen;//�u���[���p�A���P�x�s�N�Z���ڂ����X�N���[��

        //�V�F�[�_�[�n���h��
        int _vertexShaderHandle;//�A�j���[�V�������Ȃ����f���p
        int _vertexShaderHandleSkinMesh;//�X�L�����b�V�����f���p
        int _depthToRedPS;//�[�x���ԕϊ��p�V�F�[�_�[
        int _depthToGreenPS;//�[�x���Εϊ��p�V�F�[�_�[
        int _ppShaderHandle;//�u���[�p�V�F�[�_�[
        int _ppShaderNoBlurHandle;//�u���[���g�p���Ȃ��V�F�[�_�[

        bool _blur;
        void Import();

    };
}