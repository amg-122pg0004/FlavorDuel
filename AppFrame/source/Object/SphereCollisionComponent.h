/*****************************************************************//**
 * \file   CollisionComponent.h
 * \brief  ����R���W����
 *
 * \author �y�������Y
 * \date   December 2022
 *********************************************************************/
#pragma once
#include "ComponentBase.h"
namespace AppFrame {
    class  SphereCollisionComponent :public ComponentBase
    {
    public:
        SphereCollisionComponent();
        ~SphereCollisionComponent();
        bool Init()override;
        void Update(InputManager& input)override;
        void Render()override;
        void Debug()override;
        VECTOR GetPosition();
        void SetRadius(float value) { _radius = value; }
        float GetRadius() { return _radius; }
        void SetAttachFrame(int value) { _attachFrame = value; }
        int GetAttachFrame() { return _attachFrame; }
        void SetOffset(VECTOR value) { _offset = value; }
        VECTOR GetOffset() { return _offset; }

    private:
        VECTOR _offset;//�e�I�u�W�F�N�g�̃��[�g�A���邢�̓A�^�b�`�{�[������̈ʒu�I�t�Z�b�g��
        float _radius;//����R���W�����T�C�Y�p
        int _attachFrame;//�A�^�b�`����Ă���t���[���i�{�[���̕ʏ́j
    };
}