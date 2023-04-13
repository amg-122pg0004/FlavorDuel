/*****************************************************************//**
 * \file   CharacterCodeConvert.h
 * \brief  文字コード変更のためのクラス
 * 
 * \author 土居将太郎
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
         * \brief UTF-8をUTF-16に変更
         * \param utf8 UTF-8の文字列
         * \return UTF-16の文字列
         */
        static std::wstring ConvertUTF8ToWide(const std::string& utf8);
        /**
         * \brief UTF-16をShift-JISに変更
         * \param utf16 UTF-16の文字列
         * \return shift-JISの文字列
         */
        static std::string ConvertWideToMultiByte(const std::wstring& utf16);
    };
}