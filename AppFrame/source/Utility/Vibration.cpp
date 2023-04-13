/*****************************************************************//**
 * \file   Vibration.cpp
 * \brief  �R���g���[���[�U�����s�����̔�������N���X
 *
 * \author �y�������Y
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