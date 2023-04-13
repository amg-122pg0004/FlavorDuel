/*****************************************************************//**
 * \file   MV1Component.h
 * \brief  MV1�̃g�����X�t�H�[���X�V�A�`��A�A�j���[�V�����t���[���̐i�s�@�\
 *
 * \author �y�������Y
 * \date   November 2022
 *********************************************************************/
#pragma once
#include "Object/ComponentBase.h"
#include <functional>
#include <algorithm>
#include <vector>
namespace AppFrame {
    class AnimationComponent;
    class MV1Component :public ComponentBase
    {
    public:
        MV1Component(int modelHandle);
        ~MV1Component();
        bool Init()override;
        void Update(InputManager& input)override;
        void Render()override;
        void Debug()override;
        void SetModelHandle(int modelHandle);
        int GetModelHandle() { return _modelHandle; }
        void SetAnimation(int index);
        void SetAnimSpeed(float value) { _animSpeed = value; };
        void SetValid(bool valid) { _isValid = valid; }
        void SetAttachIndex(int index) { _attahIndex = index; }
        /**
         * \brief �A�j���[�V�����̓���̃^�C�~���O�ŌĂяo���֐���ǉ�����
         * \param animIndex�@�A�j���[�V�����̔ԍ�
         * \param activateTime�@�A�j���[�V�����̎���
         * \param function �Ăяo���֐�
         */
        void AddAnimFunction(int animIndex, float activateTime, std::function<void(void)> function);

        void SetOriginalShader(const CHAR* vertexShaderPath, const CHAR* pixelShaderPath);
        void AddShaderBuffer(std::function<FLOAT4()> func, bool usePixelShader);

        void SetBloom(bool flag) { _bloom = flag; }
    private:
        /**
         * \brief �^�C�~���O���m�F���āA�A�j���[�V�����ɕR�Â��֐����Ăяo��
         * \param preTime�@�O�t���[���̃A�j���[�V��������
         * \param nowTime�@���݃t���[���̃A�j���[�V��������
         */
        void CheckAnimFunction(float preTime, float nowTime);

        //�`��O�̃V�F�[�_�[�̐ݒ�
        void SetShader();

        bool _isValid;
        int _modelHandle;
        int _animIndex;
        int _attahIndex;
        float _playTime, _totalTime;
        float _animSpeed;
        std::vector<std::vector<std::pair<float, std::function<void(void)>>>> _animFunction;//[�A�j���[�V����Index][����,�Ăяo���֐�]

        bool _useOriginalShader;
        int _vertexShader;
        int _pixelShader;

        struct shaderBuffer {
            int _bufferHandle{ -1 };
            int _slot{ 1 };
            std::function < FLOAT4() > _getter;
            bool _usePixelShader{ true };//false�Ȃ�vertex�V�F�[�_�[�Ŏg�p
        };
        std::vector<shaderBuffer> _constantBufferArray;

        bool _bloom;
    };
}
