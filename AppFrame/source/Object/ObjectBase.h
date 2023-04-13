/*****************************************************************//**
 * \file   ObjectBase.h
 * \brief  �I�u�W�F�N�g�̐e�N���X
 * \brief  Transform�����B2D�I�u�W�F�N�g��_position x,y�݂̂��g�p����
 * \brief  Update,Render,Debug�͏��L�R���|�[�l���g�̊֐��Ăяo�����s���Ă��邽�ߌp����ŕK���Ă�
 *
 * \author �y�������Y
 * \date   November 2022
 *********************************************************************/

#pragma once
#include <DxLib.h>
#include <string>
#include <map>
#include <memory>
#include <typeindex>

#include "MessageList.h"
#include "../AppFrameMath.h"

namespace AppFrame {

    class InputManager;
    class ModeBase;
    class ComponentBase;
    class ObjectBase {
    public:
        ObjectBase();
        virtual ~ObjectBase();
        //�I�u�W�F�N�g�T�[�o�[�ɒǉ������ۂɌĂ΂��
        virtual void Init();
        //�I�u�W�F�N�g�T�[�o�[����폜���ꂽ�ۂɌĂ΂��
        virtual void Terminate();
        virtual void Update(InputManager& input);
        virtual void Render();
        virtual void Debug();

        VECTOR GetPosition()const { return _position; }
        VECTOR GetRotation()const { return _rotation; }
        VECTOR GetScale()const { return _scale; }
        virtual void SetPosition(VECTOR position) { _position = position; }
        virtual void SetPosition(int positionX, int positionY) { _position = { static_cast<float>(positionX), static_cast<float>(positionY), 0.0f }; }
        virtual void SetPosition(VECTOR2<int> position2D) { _position = { static_cast<float>(position2D.x), static_cast<float>(position2D.y), 0.0f }; }
        virtual void SetRotation(VECTOR rotation) { _rotation = rotation; }
        virtual void SetScale(VECTOR scale) { _scale = scale; }
        MATRIX GetPositonMatrix()const { return _positionMatrix; }
        MATRIX GetRotationMatrix()const { return _rotationMatrix; }
        MATRIX GetScaleMatrix()const { return _scaleMatrix; }
        MATRIX GetTransform()const { return _transrom; }

        virtual bool IsDead()const { return _dead; }
        virtual void Dead() { _dead = true; }

        bool GetVisible()const { return _visible; }
        void SetVisible(bool flag) { _visible = flag; }
        int GetLayer()const { return _layer; }
        void SetLayer(int value) { _layer = value; }
        int GetID()const { return _id; }
        void SetID(int value) { _id = value; }
        std::string_view GetName()const { return _name; }
        void SetName(std::string string) { _name = string; }
        ModeBase* GetMode()const { return _mode; }
        void SetMode(ModeBase* mode) { _mode = mode; }

        //���^�R���|�[�l���g��ǉ�����ۂ͈قȂ�ID��ݒ肷��
        virtual void AddComponent(std::unique_ptr<ComponentBase> component, int id = 0);

        /**
         * \brief �w��̃R���|�[�l���g���擾����@��FGetComponent<MV1Component>()
         * \return �R���|�[�l���g�̃|�C���^��Ԃ��B�������Ă��Ȃ����nullptr��Ԃ��B
         */
        template <typename C>
        C* GetComponent(int id = 0) {
            C* result = nullptr;

            if (_components.count({ typeid(C), id }) != 0) {
                result = static_cast<C*>(_components[ {typeid(C), id}].get());
            }
            return result;
        }

        /**
         * \brief �w��̃N���X���m�F����@��FCheckType<Player>()�ACheckType<Enemy>()
         * \return �w��̃N���X�ł����true��Ԃ�
         */
        template <typename T>
        bool CheckType()const {
            if (typeid(T&) == typeid(*this)) {
                return true;
            }

            return false;
        }

        /**
         * \brief �I�u�W�F�N�g�ԂŒʐM���s�������ꍇ�Ɏg����ėp�I�Ȋ֐��ł��B��:object->MessageEvent(*this,"damage");
         * \param messenger ���b�Z�[�W�̔��M��
         * \param message ���b�Z�[�W�̓��e
         * \return �������������s������True��Ԃ�
         */
        virtual bool MessageEvent(ObjectBase* const messenger, const MessageContainer& message) {
            return false;
        }
        /**  \brief �S�ẴI�u�W�F�N�g�փ��b�Z�[�W�𑗐M*/
        bool SendMessageAllObjects(const MessageContainer& message);
        /**  \brief �I�u�W�F�N�g�փ��b�Z�[�W�𑗐M*/
        bool SendMessageOneObject(ObjectBase* const destination, const MessageContainer& message);

    protected:
        bool _visible;//Render�ŕ`�悷�邩�̔���Ɏg�p

        std::string		_name;//�I�u�W�F�N�g�ɖ��O��t���Č������\
        int				_id;//�C���X�^���X�쐬���ɌŗL��ID������U����A�������\
        int				_layer;//�`�揇

        VECTOR _position;
        VECTOR _rotation;
        VECTOR _scale;
        MATRIX _positionMatrix;
        MATRIX _rotationMatrix;
        MATRIX _scaleMatrix;
        MATRIX _transrom;
        bool _dead;

        std::map<std::pair<std::type_index, int>, std::unique_ptr<ComponentBase>> _components;

        ModeBase* _mode;
    };
}
