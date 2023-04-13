/*****************************************************************//**
 * \file   Vibration.h
 * \brief  �R���g���[���[�U�����s�����̔�������N���X
 *
 * \author �y�������Y
 * \date   March 2023
 *********************************************************************/
#pragma once
namespace AppFrame {
    class Vibration
    {
    public:
        Vibration();
        ~Vibration();
        static Vibration* GetInstance() { return _lpInstance; }
        bool GetActivate() { return _activate; }
        void SetActivate(bool flag) { _activate = flag; }

    private:
        static	Vibration* _lpInstance;
        bool _activate;
    };
}