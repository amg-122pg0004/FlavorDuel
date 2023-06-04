/*****************************************************************//**
 * \file   ApplicationMain.h
 * \brief  WinMain‚©‚çŒÄ‚Î‚ê‚éƒNƒ‰ƒX
 * 
 * \author “y‹«‘¾˜Y
 * \date   May 2023
 *********************************************************************/
#pragma once
#include "appframe.h"
#include "CardDataStruct.h"

namespace Flavor {
	class ApplicationMain :public AppFrame::ApplicationBase
	{
	public:
		ApplicationMain();
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