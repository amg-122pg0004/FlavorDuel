/*****************************************************************//**
 * \file   UserDataStruct.h
 * \brief  ���[�U�[�f�[�^
 *         �f�[�^�T�[�o�[�ɕۑ�����Ă���user_data�e�[�u���Ɠ���
 * 
 * \author �y�������Y
 * \date   May 2023
 *********************************************************************/
#pragma once
#include <string>
#include <vector>
namespace Flavor {
	struct UserData
	{
		std::string id = "";
		std::string password = "";
		int level = 1;
		int money = 0;
		int rank = 1000;
	};
}