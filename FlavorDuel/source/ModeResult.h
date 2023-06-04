#pragma once
#include "appframe.h"
namespace Flavor {
	using AppFrame::InputManager;
	class ModeInGame;
	class ModeResult :public AppFrame::ModeBase {
	public:
		ModeResult(ModeInGame& modeInGmame,bool win);
		bool Initialize()override;
		bool Terminate()override;
		bool Update(InputManager& input)override;
		bool Render()override;
		bool Debug()override;

		void ChangeModeHome();
	private:
		ModeInGame& _modeInGame;
		bool _win;
	};
}