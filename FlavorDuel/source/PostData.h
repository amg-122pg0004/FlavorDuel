/*****************************************************************//**
 * \file   PostData.h
 * \brief  httpでデータをPOSTする別スレッド処理クラス
 * 
 * \author 土居将太郎
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