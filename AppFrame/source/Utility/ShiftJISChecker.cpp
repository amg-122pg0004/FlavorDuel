/*****************************************************************//**
 * \file   ShiftJISChecker.cpp
 * \brief  ShiftJISの文字を確認するクラス
 *
 * \author 土居将太郎
 * \date   January 2023
 *********************************************************************/
#include "ShiftJISChecker.h"
namespace AppFrame {
    int ShiftJISChecker::Check(unsigned char uc) {
        if (uc < 0x81) { return 1; }

        if (uc < 0xa0) { return 2; }

        if (uc < 0xe0) { return 1; }

        if (uc < 0xff) { return 2; }

        return 1;
    }
}