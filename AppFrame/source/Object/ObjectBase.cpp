/*****************************************************************//**
 * \file   ObjectBase.cpp
 * \brief  オブジェクトの親クラス
 * \brief  Transformを持つ。2Dオブジェクトは_position X,Yのみを使用する
 * \brief  Update,Render,Debugは所有コンポーネントの関数呼び出しを行っているため継承先で必ず呼ぶ
 *
 * \author 土居将太郎
 * \date   November 2022
 *********************************************************************/
#include "ObjectBase.h"
#include "Resource/ModelServer.h"
#include "../Mode/ModeBase.h"
#include "ComponentBase.h"
#include "ObjectServer.h"
namespace AppFrame {

    AppFrame::ObjectBase::ObjectBase()
        : _position{ 0, 0, 0 }
        , _rotation{ 0, 0, 0 }
        , _scale{ 1, 1, 1 }
        , _dead{ false }
        , _visible{ true }
        , _name{ "null" }
        , _id{ -1 }
        , _layer{ 0 }
        , _mode{ nullptr }
    {

    }

    ObjectBase::~ObjectBase()
    {
        _components.clear();
    }

    void ObjectBase::Init()
    {
    }

    void ObjectBase::Terminate()
    {
        //_components.clear();
    }

    void ObjectBase::Update(InputManager& input)
    {
        _positionMatrix = MGetTranslate(_position);
        _rotationMatrix = MMult(MMult(MGetRotX(_rotation.x), MGetRotY(_rotation.y)), MGetRotZ(_rotation.z));
        _scaleMatrix = MGetScale(_scale);

        for (auto&& component : _components) {
            component.second->Update(input);
        }
    }

    void ObjectBase::Render()
    {
        if (!_visible) {
            return;
        }

        for (auto&& component : _components) {
            component.second->Render();
        }
    }

    void ObjectBase::Debug()
    {
        for (auto&& component : _components) {
            component.second->Debug();
        }
    }

    void ObjectBase::AddComponent(std::unique_ptr<ComponentBase> component, int id)
    {
        component->SetParent(this);

        if (component->Init()) {
            _components[ {typeid(*component), id}] = (std::move(component));
        }
    }

    bool ObjectBase::SendMessageAllObjects(const MessageContainer& message)
    {
        bool result{ false };

        if (_mode->GetObjectServer()->SendMessageAllObjects(this, message)) {
            result = true;
        }

        return result;
    }

    bool ObjectBase::SendMessageOneObject(ObjectBase* const destination, const MessageContainer& message)
    {
        return _mode->GetObjectServer()->SendMessageOneObject(this, message, destination);
    }

}