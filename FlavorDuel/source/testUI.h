#pragma once
#include "appframe.h"
using AppFrame::InputManager;
class testUI : public AppFrame::UICanvas
{
public:
	testUI();
	void Init();
	void Terminate();
	void Update(InputManager& input, float deltaSeconds);
	void Render();
};

