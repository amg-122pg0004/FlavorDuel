/*****************************************************************//**
 * \file   Vibration.cpp
 * \brief  コントローラー振動を行うかの判定を持つクラス
 *
 * \author 土居将太郎
 * \date   March 2023
 *********************************************************************/
#include "Vibration.h"

namespace AppFrame {
    Vibration* Vibration::_lpInstance = nullptr;

    Vibration::Vibration()
    {
        _lpInstance = this;
        _activate = true;
    }

    Vibration::~Vibration()
    {
        _lpInstance = nullptr;
    }

}