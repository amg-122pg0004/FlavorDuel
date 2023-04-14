#pragma once
#include "appframe.h"
#include "CardDataStruct.h"
using AppFrame::InputManager;
namespace Flavor {
	class ModeTest : public AppFrame::ModeBase
	{
	public:
		ModeTest();
		bool Initialize();
		bool Terminate();
		bool Update(InputManager& input);
		bool Render();
		bool Debug();
	private:
		CardData _testCard;
	};
}