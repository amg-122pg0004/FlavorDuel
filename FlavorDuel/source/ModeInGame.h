#pragma once
#include "appframe.h"
#include "CardDataStruct.h"
#include "ISubjectSequence.h"
#include "CardFactory.h"
namespace Flavor {
	using AppFrame::InputManager;
	class CardFactory;
	class MessageLog;

	class ModeInGame : public AppFrame::ModeBase, private ISubjectSequence {
	public:
		ModeInGame(DeckData myData, DeckData opponentData);
		bool Initialize();
		bool Terminate();
		bool Update(InputManager& input);
		bool Render();
		bool Debug();
		void Subscribe(IObserverSequence* observer)override;
		void Notify(SequenceMessages message)override;

		std::unique_ptr<CardFactory>& GetCardFactory() { return _cardFactory; }
		MessageLog* GetMessageLog() { return _messageLog; }
	private:
		std::unique_ptr<CardFactory> _cardFactory;
		MessageLog* _messageLog;
		DeckData _myData;
		DeckData _opponentData;
	};
}