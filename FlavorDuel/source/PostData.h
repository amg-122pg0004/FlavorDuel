/*****************************************************************//**
 * \file   PostData.h
 * \brief  http�Ńf�[�^��POST����ʃX���b�h�����N���X
 * 
 * \author �y�������Y
 * \date   May 2023
 *********************************************************************/
#pragma once
#include "appframe.h"
#include "Curl.h"
#include "ThreadBase.h"
#include "CardDataStruct.h"
#include "UserDataStruct.h"

namespace Flavor {
	class CardObject;
	class PostThread : public ThreadBase {
	public:
		PostThread(CardObject* card);
		bool ThreadProc()override;
		CardObject* GetCard() { return _card; }
	private:
		CardObject* _card;
	};

}