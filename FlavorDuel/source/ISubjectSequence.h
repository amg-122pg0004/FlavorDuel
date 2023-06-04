#pragma once
#include <vector>
#include "SequenceMessages.h"

namespace Flavor {
	class IObserverSequence;
	class ISubjectSequence {
	public:
		ISubjectSequence() {}
		virtual ~ISubjectSequence() {}
		virtual void Subscribe(IObserverSequence* observer) = 0;
		virtual void Notify(InGameSequence message) = 0;

		std::vector<IObserverSequence*>& GetObserverList() { return _observerList; }
		void SetSequence(InGameSequence sequence) { _sequence = sequence; }
		InGameSequence GetSequence() { return _sequence; }
	private:
		std::vector<IObserverSequence*> _observerList;
		InGameSequence _sequence;
	};
}