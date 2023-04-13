#pragma once
#include "appframe.h"
namespace Flavor {
	class ApplicationMain :public AppFrame::ApplicationBase
	{
	public:
		bool Initialize(HINSTANCE hInstance);
		bool Input();
		bool Update();
		bool Render();
		bool Debug();
	private:
		bool _debug;
	};
}