#pragma once
#include "SequenceMessages.h"
namespace Flavor {
	class IObserverSequence {
	public:
		virtual ~IObserverSequence() {}
		virtual void ReceiveNotify(SequenceMessages message) = 0;
	};
}

