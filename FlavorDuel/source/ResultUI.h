#pragma once
#include "appframe.h"
#include "ResultType.h"
namespace Flavor {
	using AppFrame::InputManager;
	class ModeResult;
	class ResultUI :public AppFrame::UICanvas
	{
	public:

		ResultUI(ModeResult& mode, ResultType type);
		~ResultUI();
		void Init()override;
		void Terminate()override;
		void Update(InputManager& input, float deltaSeconds)override;
		void Render()override;

	private:
		ModeResult& _modeResult;
	};
}