/*****************************************************************//**
 * \file   ObjectServer.h
 * \brief  �Q�[�����̃I�u�W�F�N�g�z����Ǘ�����
 * \brief  �z��ւ̒ǉ��폜�A�X�V�`��̌Ăяo���A�����A���b�Z�[�W���M�̋@�\������
 *
 * \author �y�������Y
 * \date   December 2022
 *********************************************************************/
#pragma once
#include <DxLib.h>
#include <memory>
#include <vector>
#include <algorithm>
#include <string>
#include "MessageList.h"
namespace AppFrame {
    class ObjectBase;
    class InputManager;
    class ModeBase;

    class ObjectServer {

    public:
        ObjectServer(ModeBase& parent);
        ~ObjectServer();

        std::vector<std::unique_ptr<ObjectBase>>& GetObjects() { return _objects; }

        void Clear();

        /** Actor���y���f�B���O�ɒǉ����� */
        void Add(std::unique_ptr<ObjectBase> actor);
        //����̃I�u�W�F�N�g���폜����
        void Delete(ObjectBase& actor);
        void Update(InputManager& input);
        void Render(int renderScreen = DX_SCREEN_BACK);
        void Debug();

        ObjectBase* Get(const int id);
        ObjectBase* Get(std::string name);

    private:
        std::vector<std::unique_ptr<ObjectBase>> _objects;
        std::vector<std::unique_ptr<ObjectBase>> _pendingObjects;

        bool _updating;

        //�y���f�B���O��Actor���Q�[�����ɒǉ�
        void AddPendingObject();
        //dead�t���O�������Ă���I�u�W�F�N�g��S�č폜
        void DeleteObject();

        int _uidCount;
        ModeBase& _mode;
    };
}
