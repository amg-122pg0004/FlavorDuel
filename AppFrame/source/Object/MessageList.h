/*****************************************************************//**
 * \file   MessageList.h
 * \brief  �I�u�W�F�N�g�ԒʐM�Ɏg�p���郁�b�Z�[�W���̎擾�C���^�[�t�F�[�X�ł�
 *
 * \author �y�������Y
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