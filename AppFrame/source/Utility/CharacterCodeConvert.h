/*****************************************************************//**
 * \file   CharacterCodeConvert.h
 * \brief  �����R�[�h�ύX�̂��߂̃N���X
 * 
 * \author �y�������Y
 * \date   April 2023
 *********************************************************************/
#pragma once
#include <string>
#include <tchar.h>
#include <vector>
namespace AppFrame {
    class CharacterCodeConvert {
    public:
        /**
         * \brief UTF-8��UTF-16�ɕύX
         * \param utf8 UTF-8�̕�����
         * \return UTF-16�̕�����
         */
        static std::wstring ConvertUTF8ToWide(const std::string& utf8);
        /**
         * \brief UTF-16��Shift-JIS�ɕύX
         * \param utf16 UTF-16�̕�����
         * \return shift-JIS�̕�����
         */
        static std::string ConvertWideToMultiByte(const std::wstring& utf16);
    };
}