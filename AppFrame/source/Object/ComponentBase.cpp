/*****************************************************************//**
 * \file   ComponentBase.h
 * \brief  コンポーネントの基底クラス
 * \brief  複数のオブジェクトが共通して使いたい機能はコンポーネントにして各自持たせる
 * \brief  SetParentはオブジェクト側から呼ばれるのでコンポーネント内では使用しない
 *
 * \author 土居将太郎
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