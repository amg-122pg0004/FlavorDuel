/*****************************************************************//**
 * \file   ShiftJISChecker.h
 * \brief  ShiftJIS�̕������m�F����N���X
 * 
 * \author �y�������Y
 * \date   January 2023
 *********************************************************************/
#pragma once
namespace AppFrame {
    class ShiftJISChecker
    {
    public:
        static	int Check(unsigned char uc);
        static	int Check(char c) { return Check((unsigned char)c); }
    };

}