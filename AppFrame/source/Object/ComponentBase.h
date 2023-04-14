/*****************************************************************//**
 * \file   ComponentBase.h
 * \brief  コンポーネントの基底クラス
 * \brief  複数のオブジェクトが共通して使いたい機能はコンポーネントにして各自持たせる
 * \brief  SetParentはオブジェクト側から呼ばれるのでコンポーネント内では使用しない
 *
 * \author 土居将太郎
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