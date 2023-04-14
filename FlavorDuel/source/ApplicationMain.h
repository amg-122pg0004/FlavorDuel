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
		virtual int DispSizeW() { return 1280; }
		virtual int DispSizeH() { return 720; }
	private:
		bool _debug;
	};
}