#pragma once
#include "appframe.h"
namespace Flavor {
	using AppFrame::InputManager;
	class ModeResult;
	class ResultUI :public AppFrame::UICanvas
	{
	public:
		ResultUI(ModeResult& mode,bool win);
		~ResultUI();
		void Init()override;
		void Terminate()override;
		void Update(InputManager& input, float deltaSeconds)override;
		void Render()override;

	private:
		ModeResult& _modeResult;
	};
}