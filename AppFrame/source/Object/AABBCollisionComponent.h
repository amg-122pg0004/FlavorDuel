/*****************************************************************//**
 * \file   AABBCollisionComponent.h
 * \brief  AABB(���[���h���W���ɉ��������`��)�R���W����
 *
 * \author �y�������Y
 * \date   April 2023
 *********************************************************************/
#pragma once
#include "ComponentBase.h"
#include <DxLib.h>
namespace AppFrame {
    class AABBCollisionComponent :public ComponentBase
    {
    public:
        bool Init()override;
        void Update(InputManager& input)override;
        void Render()override;
        void Debug()override;
        VECTOR GetPosition();
        void SetSize(VECTOR value) { _size = value; }
        VECTOR GetSize() { return _size; }
        void SetAttachFrame(int value) { _attachFrame = value; }
        int GetAttachFrame() { return _attachFrame; }
        void SetOffset(VECTOR value) { _offset = value; }
        VECTOR GetOffset() { return _offset; }
    private:
        VECTOR _offset;//�e�I�u�W�F�N�g�̃��[�g�A���邢�̓A�^�b�`�{�[������̈ʒu�I�t�Z�b�g��
        VECTOR _size;//����R���W�����T�C�Y�p
        int _attachFrame;//�A�^�b�`����Ă���t���[���i�{�[���̕ʏ́j
    };
}