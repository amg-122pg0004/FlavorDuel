#include "CharacterCodeConvert.h"
#include <windows.h>

namespace {
    constexpr auto EMPTY_STR = _T("");
    constexpr auto EMPTY_WSTR = L"";
    constexpr auto DELIMITER = _T(", ");
}
namespace AppFrame {
    //! @fn std::wstring ScriptsData::ConvertUTF8ToWide(const std::string& utf8) const
    //! @brief UTF-8 文字コードの std::string を std::wstring(UTF-16) に変換する
    //! @param[in] utf8 UTF-8 文字コードの std::string
    //! @return UTF-16 文字コードの std::wstring
    //!
    std::wstring CharacterCodeConvert::ConvertUTF8ToWide(const std::string& utf8)
    {
        if (utf8.empty()) {
            return EMPTY_WSTR;
        }

        const auto inLength = static_cast<int>(utf8.length());
        const auto outLength = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), inLength, 0, 0);

        if (outLength <= 0) {
            return EMPTY_WSTR;
        }

        std::vector<wchar_t> buffer(outLength);

        MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), inLength, &(buffer[0]), outLength);

        std::wstring utf16(buffer.begin(), buffer.end());

        return std::move(utf16);
    }


    //!
    //! @fn std::string ScriptsData::ConvertWideToMultiByte(const std::wstring& utf16) const
    //! @brief std::wstring(UTF-16) をマルチバイト文字コードの std::string に変換する
    //! @param[in] utf16 UTF-16 文字コードの std::wstring
    //! @return マルチバイト文字コードの std::string
    //!
    std::string CharacterCodeConvert::ConvertWideToShiftJIS(const std::wstring& utf16)
    {
        if (utf16.empty()) {
            return EMPTY_STR;
        }

        const auto inLength = static_cast<int>(utf16.length());
        const auto outLength = WideCharToMultiByte(CP_ACP, 0, utf16.c_str(), inLength, 0, 0, 0, 0);

        if (outLength <= 0) {
            return EMPTY_STR;
        }

        std::vector<char> buffer(outLength);

        WideCharToMultiByte(CP_ACP, 0, utf16.c_str(), inLength, &(buffer[0]), outLength, 0, 0);

        std::string mbs(buffer.begin(), buffer.end());

        return std::move(mbs);
    }

    std::string CharacterCodeConvert::ConvertShiftJISToUTF8(const std::string& shiftJIS)
    {
        if (shiftJIS.empty()) {
            return EMPTY_STR;
        }

        const auto lengthShiftJIS = static_cast<int>(shiftJIS.length());
        const auto lengthUtf16= MultiByteToWideChar(CP_ACP, 0, shiftJIS.c_str(), lengthShiftJIS, 0, 0);

        if (lengthUtf16 <= 0) {
            return EMPTY_STR;
        }
        std::vector<wchar_t> wcharBuffer(lengthUtf16);

        MultiByteToWideChar(CP_ACP, 0, shiftJIS.c_str(), lengthShiftJIS, &(wcharBuffer[0]), lengthUtf16);
        std::wstring utf16(wcharBuffer.begin(), wcharBuffer.end());

        const auto lengthUTF8 = WideCharToMultiByte(CP_UTF8, 0, utf16.c_str(), lengthUtf16, 0, 0, 0, 0);

        if (lengthUTF8 <= 0) {
            return EMPTY_STR;
        }

        std::vector<char> charBuffer(lengthUTF8);

        WideCharToMultiByte(CP_UTF8, 0, utf16.c_str(), lengthUtf16, &(charBuffer[0]), lengthUTF8, 0, 0);
        std::string mbs(charBuffer.begin(), charBuffer.end());

        return  std::move(mbs);
    }
}