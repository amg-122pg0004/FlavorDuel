/*****************************************************************//**
 * \file   PostData.h
 * \brief  http�Ńf�[�^��POST����ʃX���b�h�����N���X
 *
 * \author �y�������Y
 * \date   May 2023
 *********************************************************************/
#pragma once
#include "ThreadBase.h"
#include "UserDataStruct.h"
namespace Flavor
{
	class CardObject;
	class RegisterThread : public ThreadBase {
	public:
		RegisterThread(std::string id, std::string password);
		bool ThreadProc()override;
		UserData GetUserData() { return _data; }
		bool GetSuccess() { return _success; }
	private:
		std::string _id;
		std::string _password;
		bool _success;
		UserData _data;
	};
};

