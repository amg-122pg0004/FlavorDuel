#pragma once
#include "appframe.h"
namespace Flavor {
	using AppFrame::InputManager;
	class ModeHome :public AppFrame::ModeBase {
	public:
		ModeHome();
		bool Initialize();
		bool Terminate();
		bool Update(InputManager& input);
		bool Render();
		bool Debug();
	private:
	};
}