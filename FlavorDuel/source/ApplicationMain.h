/*****************************************************************//**
 * \file   ApplicationMain.h
 * \brief  WinMain����Ă΂��N���X
 * 
 * \author �y�������Y
 * \date   May 2023
 *********************************************************************/
#pragma once
#include "appframe.h"
#include "CardDataStruct.h"
namespace {
	std::vector<Flavor::CardData> TestDeck = {
		{{"����","�׈��ȐS�������Ă���",0},
		{"�h���S��","����f���A�X��R�₷",1},
		{"�傫�ȋT","�ł��b���Őg������Ă���",2},
		{"�S�u����","���錫���A�W�c�ōs�����邠������������������������",3},
		{"�R�m","���`���d�񂶂�R�m",4},
		{"���J�J�}�L��","���̋���Ȋ��͂ǂ�ȏ����ؒf�\��������������",5},
		{"���̗r","���ɏo�Ă���ƕs�g�Ȃ��Ƃ��N����炵��",6},
		{"�X���C��","�J���z�����Đ����Ă���",7},
		{"�g�����g","�ʂ肪�������l�Ɋ��݂���",8},
		{"���@�g��","5�����̖��@�𑀂�",9}}
	};
}
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