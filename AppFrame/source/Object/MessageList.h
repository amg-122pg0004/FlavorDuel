/*****************************************************************//**
 * \file   MessageList.h
 * \brief  オブジェクト間通信に使用するメッセージ情報の取得インターフェースです
 *
 * \author 土居将太郎
 * \date   February 2023
 *********************************************************************/
#pragma once
#include <string>


class MessageContainer {
public:
    MessageContainer() { ; }
    virtual ~MessageContainer() { ; }
    virtual std::string_view GetTitle()const = 0;
    virtual float GetValue()const = 0;
    virtual std::string_view GetText()const = 0;
};