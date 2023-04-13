/*****************************************************************//**
 * \file   ShiftJISChecker.cpp
 * \brief  ShiftJIS�̕������m�F����N���X
 *
 * \author �y�������Y
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