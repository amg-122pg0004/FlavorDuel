/*****************************************************************//**
 * \file   MessageWindow.h
 * \brief  �C���Q�[����ʉE���ɕ\������郁�b�Z�[�W1��
 *         MessageLog�̎q�Ƃ��Ēǉ�����Ă���
 * 
 * \author �y�������Y
 * \date   May 2023
 *********************************************************************/
#pragma once
#include "appframe.h"
namespace Flavor {
	using AppFrame::InputManager;
	class MessageWindow :public AppFrame::UICanvas
	{
	public:
		MessageWindow(std::string message);
		void Init();
		void Terminate();
		void Update(InputManager& input, float deltaSeconds);
		void Render();
	private:
	};
}
