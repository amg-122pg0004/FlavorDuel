/*****************************************************************//**
 * \file   UserDataStruct.h
 * \brief  ユーザーデータ
 *         データサーバーに保存されているuser_dataテーブルと同じ
 * 
 * \author 土居将太郎
 * \date   May 2023
 *********************************************************************/
#pragma once
#include <string>
#include <vector>
namespace Flavor {
	struct UserData
	{
		std::string id;
		std::string password;
		int level;
		int money;
		int rank;
	};
}