/*****************************************************************//**
 * \file   ComponentBase.h
 * \brief  �R���|�[�l���g�̊��N���X
 * \brief  �����̃I�u�W�F�N�g�����ʂ��Ďg�������@�\�̓R���|�[�l���g�ɂ��Ċe����������
 * \brief  SetParent�̓I�u�W�F�N�g������Ă΂��̂ŃR���|�[�l���g���ł͎g�p���Ȃ�
 *
 * \author �y�������Y
 * \date   December 2022
 *********************************************************************/
#pragma once
#include <DxLib.h>
namespace AppFrame {
    class ObjectBase;
    class InputManager;
    class ComponentBase {
    public:
        ComponentBase();
        ~ComponentBase();
        virtual bool Init();
        virtual void Update(InputManager& input);
        virtual void Render();
        virtual void Debug();

        virtual void SetParent(ObjectBase* parent) { _parent = parent; }
    protected:
        ObjectBase* _parent;
    };


}