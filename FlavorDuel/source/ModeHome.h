/*****************************************************************//**
 * \file   ModeHome.h
 * \brief  �z�[����ʃ��[�h
 * 
 * \author �y�������Y
 * \date   May 2023
 *********************************************************************/
#pragma once
#include "appframe.h"
namespace Flavor {
	using AppFrame::InputManager;
	class ModeHome :public AppFrame::ModeBase {
	public:
		ModeHome();
		bool Initialize();
		bool Terminate();
		bool Update(InputManager& input);
		bool Render();
		bool Debug();

		//�}�b�`���O���[�h���쐬����
		void OpenMatching();
		//�f�b�L�ҏW���[�h�Ɉړ�����
		void ChangeModeDeckEdit();
	private:
	};
}