/*****************************************************************//**
 * \file   Vibration.h
 * \brief  コントローラー振動を行うかの判定を持つクラス
 *
 * \author 土居将太郎
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