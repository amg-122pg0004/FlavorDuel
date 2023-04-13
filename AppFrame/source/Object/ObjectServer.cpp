/*****************************************************************//**
 * \file   ObjectServer.cpp
 * \brief  �Q�[�����̃I�u�W�F�N�g�z����Ǘ�����
 * \brief  �z��ւ̒ǉ��폜�A�X�V�`��̌Ăяo���A�����A���b�Z�[�W���M�̋@�\������
 *
 * \author �y�������Y
 * \date   December 2022
 *********************************************************************/
#include "ObjectServer.h"
#include "ModeBase.h"
#include "ObjectBase.h"
#include "ApplicationBase.h"
#include "BlurRenderer.h"
#include "ChangeScreen.h"

namespace AppFrame {


    ObjectServer::ObjectServer(ModeBase& parent)
        :_uidCount{ 0 }, _mode{ parent }
    {
        Clear();
    }

    ObjectServer::~ObjectServer()
    {
        _objects.clear();
    }

    void ObjectServer::Clear()
    {
    }

    void ObjectServer::Add(std::unique_ptr<ObjectBase> object)
    {
        object->SetMode(&_mode);
        ++_uidCount;
        object->SetID(_uidCount);
        object->Init();

        if (_updating) {
            _pendingObjects.push_back(std::move(object));
        }
        else {
            _objects.push_back(std::move(object));
        }
    }

    void ObjectServer::Delete(ObjectBase& object)
    {
        object.Dead();
    }

    namespace {
        static bool objectSort(std::unique_ptr<ObjectBase>& x, std::unique_ptr<ObjectBase>& y) {
            VECTOR position = GetCameraPosition();

            if (x->GetLayer() == y->GetLayer()) {
                return VSize(VSub(x->GetPosition(), position)) < VSize(VSub(y->GetPosition(), position));
            }

            return x->GetLayer() < y->GetLayer();
        }
    }

    void ObjectServer::Update(InputManager& input)
    {
        _updating = true;
        DeleteObject();	// �폜�\�񂳂ꂽ�I�u�W�F�N�g���폜����
        AddPendingObject();
        std::sort(_objects.begin(), _objects.end(), objectSort);

        for (auto&& actor : _objects) {
            actor->Update(input);
        }

        _updating = false;

    }

    void ObjectServer::Render(int renderScreen)
    {
        //layer9�ȉ��̕`��(�Q�[����3D���f����9�ȉ��ɐݒ肷��O��)
        auto renderUnder9Layer = [&] {
            for (auto&& actor : _objects) {
                if (actor->GetLayer() > 9) {
                    break;
                }

                actor->Render();
            }
        };
        //�s���������̕`��
        MV1SetSemiTransDrawMode(DX_SEMITRANSDRAWMODE_NOT_SEMITRANS_ONLY);
        renderUnder9Layer();
        //�s���������̕`��
        MV1SetSemiTransDrawMode(DX_SEMITRANSDRAWMODE_SEMITRANS_ONLY);
        renderUnder9Layer();

        //�u���[�𔽉f
        if (_mode.GetBlurFlag()) {
            _mode.GetPostProcess()->ApplyBlur(renderScreen);
        }
        else {
            _mode.GetPostProcess()->NotApplyBlur(renderScreen);
        }

        ChangeScreen::ChangeScreenAndSaveCamera(renderScreen);
        //layer10�ȏ�̕`��(UI��10�ȏ�ɂ���z��)
        MV1SetSemiTransDrawMode(DX_SEMITRANSDRAWMODE_ALWAYS);

        for (auto&& actor : _objects) {
            if (actor->GetLayer() < 10) {
                continue;
            }

            actor->Render();
        }
    }

    void ObjectServer::Debug()
    {
        for (auto&& actor : _objects) {
            actor->Debug();
        }
    }

    ObjectBase* ObjectServer::Get(const int id)
    {
        for (auto&& object : _objects) {
            if (object->GetID() == id) {
                return object.get();
            }
        }

        return nullptr;
    }

    ObjectBase* ObjectServer::Get(std::string_view name)
    {
        for (auto&& object : _objects) {
            if (object->GetName() == name) {
                return object.get();
            }
        }

        return nullptr;
    }

    bool ObjectServer::SendMessageAllObjects(ObjectBase* const messenger, const MessageContainer& message)
    {
        bool flag{ false };

        for (auto&& object : _objects) {
            if (object->MessageEvent(messenger, message)) {
                flag = true;
            }
        }

        return flag;
    }

    bool ObjectServer::SendMessageAllObjects(ObjectBase* const messenger, const MessageContainer& message, std::string_view name)
    {
        bool flag{ false };

        for (auto&& object : _objects) {
            if (object->GetName() == name) {
                if (object->MessageEvent(messenger, message)) {
                    flag = true;
                }
            }
        }

        return flag;
    }

    bool ObjectServer::SendMessageOneObject(ObjectBase* const messenger, const MessageContainer& message, ObjectBase* const destination)
    {
        if (destination == nullptr) {
            return false;
        }

        return destination->MessageEvent(messenger, message);
    }

    bool ObjectServer::SendMessageOneObject(ObjectBase* const messenger, const MessageContainer& message, const int id)
    {
        if (Get(id) == nullptr) {
            return false;
        }

        return Get(id)->MessageEvent(messenger, message);
    }

    void ObjectServer::AddPendingObject()
    {
        // Add()���ꂽ���̂�L���ɂ��A�K�v�ł���΃\�[�g���s��
        if (_pendingObjects.size() > 0) {
            auto ite = _pendingObjects.begin();

            for (; ite != _pendingObjects.end(); ++ite) {
                _objects.push_back(std::move((*ite)));
            }

            _pendingObjects.clear();
        }
    }

    void ObjectServer::DeleteObject()
    {
        // �R���e�i���C�e���[�^�ŉ�( erase���C�e���[�^��v�����Ă��邽�� )
        for (auto ite = _objects.begin(); ite != _objects.end(); ) {
            if ((*ite)->IsDead()) {
                (*ite)->Terminate();
                ite = _objects.erase(ite);		// �����object���̂��̂��폜�����
            }
            else {
                ++ite;
            }
        }
    }
}