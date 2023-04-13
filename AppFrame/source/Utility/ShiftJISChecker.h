/*****************************************************************//**
 * \file   ShiftJISChecker.h
 * \brief  ShiftJISの文字を確認するクラス
 * 
 * \author 土居将太郎
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