/*****************************************************************//**
 * \file   ComponentBase.h
 * \brief  �R���|�[�l���g�̊��N���X
 * \brief  �����̃I�u�W�F�N�g�����ʂ��Ďg�������@�\�̓R���|�[�l���g�ɂ��Ċe����������
 * \brief  SetParent�̓I�u�W�F�N�g������Ă΂��̂ŃR���|�[�l���g���ł͎g�p���Ȃ�
 *
 * \author �y�������Y
 * \date   December 2022
 *********************************************************************/
#include "ComponentBase.h"
#include "InputManager.h"
namespace AppFrame {
    ComponentBase::ComponentBase()
        :_parent{ nullptr }
    {
    }

    ComponentBase::~ComponentBase()
    {
    }

    bool ComponentBase::Init()
    {
        return true;
    }

    void ComponentBase::Update(InputManager& input)
    {
    }

    void ComponentBase::Render()
    {
    }

    void ComponentBase::Debug()
    {
    }
}