#include "CharacterCodeConvert.h"
#include <windows.h>

namespace {
    constexpr auto EMPTY_STR = _T("");
    constexpr auto EMPTY_WSTR = L"";
    constexpr auto DELIMITER = _T(", ");
}
namespace AppFrame {

    std::wstring CharacterCodeConvert::ConvertUTF8ToWide(const std::string& utf8)
    {
        if (utf8.empty()) {
            return EMPTY_WSTR;
        }

        const auto in_length = static_cast<int>(utf8.length());
        const auto out_length = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), in_length, 0, 0);

        if (out_length <= 0) {
            return EMPTY_WSTR;
        }

        std::vector<wchar_t> buffer(out_length);

        MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), in_length, &(buffer[0]), out_length);

        std::wstring utf16(buffer.begin(), buffer.end());

        return std::move(utf16);
    }

    std::string CharacterCodeConvert::ConvertWideToMultiByte(const std::wstring& utf16)
    {
        if (utf16.empty()) {
            return EMPTY_STR;
        }

        const auto in_length = static_cast<int>(utf16.length());
        const auto out_length = WideCharToMultiByte(CP_ACP, 0, utf16.c_str(), in_length, 0, 0, 0, 0);

        if (out_length <= 0) {
            return EMPTY_STR;
        }

        std::vector<char> buffer(out_length);

        WideCharToMultiByte(CP_ACP, 0, utf16.c_str(), in_length, &(buffer[0]), out_length, 0, 0);

        std::string mbs(buffer.begin(), buffer.end());

        return std::move(mbs);
    }
}