#pragma once
#include "appframe.h"
#include "Curl.h"
#include "ThreadBase.h"
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

	class PostData
	{
	public:
		static bool PostCardData(CardObject* card);
	};
}


