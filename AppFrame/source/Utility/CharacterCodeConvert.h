#pragma once
#include <string>
#include <tchar.h>
#include <vector>
namespace AppFrame {
    class CharacterCodeConvert {
    public:
        static std::wstring ConvertUTF8ToWide(const std::string& utf8);
        static std::string ConvertWideToShiftJIS(const std::wstring& utf16);
        static std::string ConvertShiftJISToUTF8(const std::string& shiftJIS);
    };
}