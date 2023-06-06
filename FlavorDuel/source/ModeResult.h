#pragma once
#include "appframe.h"
#include "ResultType.h"
namespace Flavor {
	using AppFrame::InputManager;
	class ModeInGame;
	class ModeResult :public AppFrame::ModeBase {
	public:
		ModeResult(ModeInGame& modeInGmame, ResultType type);
		bool Initialize()override;
		bool Terminate()override;
		bool Update(InputManager& input)override;
		bool Render()override;
		bool Debug()override;

		void ChangeModeHome();
	private:
		ModeInGame& _modeInGame;
		ResultType _type;
	};
}