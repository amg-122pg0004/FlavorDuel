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
		{{"�h���S��","����f��"},
		{"�傫�ȋT","���ȍb���ɂ������ĕ�炵�Ă���"},
		{"���m","�Z��g�ɒ����A�傫�ȑ�������"},
		{"���@�g��","5�����̖��@�𑀂�"},
		{"�V�g","�_�̏�ɏZ�ޑ���"},
		{"�g�����g","�X�ɗ����������l�Ԃ��U������"},
		{"�m��","�񕜖��@�𓾈ӂƂ���"},
		{"�S�u����","���錫���A�W�c�ōs������"},
		{"�X���C��","�J���z�����Đ����Ă���"},
		{"�L","�����́u�ɂ�[��v"}}
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