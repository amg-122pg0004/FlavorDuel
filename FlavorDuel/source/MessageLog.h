#pragma once
#include "appframe.h"
namespace Flavor {
	using AppFrame::InputManager;
	class MessageLog: public AppFrame::UICanvas
	{
	public:
		MessageLog();
		void Init();
		void Terminate();
		void Update(InputManager& input, float deltaSeconds);
		void Render();
	};
}