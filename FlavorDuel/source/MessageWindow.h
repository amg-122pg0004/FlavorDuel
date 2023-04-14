#pragma once
#include "appframe.h"
namespace Flavor {
	using AppFrame::InputManager;
	class MessageWindow :public AppFrame::UICanvas
	{
	public:
		MessageWindow(std::string message);
		void Init();
		void Terminate();
		void Update(InputManager& input, float deltaSeconds);
		void Render();
	private:
	};
}
