/*****************************************************************//**
 * \file   Color.h
 * \brief  �g�p�p�x�̑����J���[�R�[�h�̎擾
 * 
 * \author �y�������Y
 * \date   March 2023
 *********************************************************************/
#pragma once
#include <DxLib.h>

namespace AppFrame {
    namespace Color
    {
        static const unsigned int Black = GetColor(0, 0, 0);
        static const unsigned int Gray = GetColor(125, 125, 125);
        static const unsigned int White = GetColor(255, 255, 255);
        static const unsigned int Red = GetColor(255, 0, 0);
        static const unsigned int Green = GetColor(0, 255, 0);
        static const unsigned int Blue = GetColor(0, 0, 255);
        static const unsigned int Yellow = GetColor(255, 255, 0);
        static const unsigned int LightBlue = GetColor(0, 255, 255);
        static const unsigned int Purple = GetColor(255, 0, 255);
    };
}