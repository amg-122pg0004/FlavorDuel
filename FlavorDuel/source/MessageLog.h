/*****************************************************************//**
 * \file   MessageLog.cpp
 * \brief  �C���Q�[����ʉE���ɕ\������郁�b�Z�[�W�\���g
 *         �q�Ƃ���MessageWindow���ǉ������̂ł������Ǘ�����
 *
 * \author �y�������Y
 * \date   May 2023
 *********************************************************************/
#pragma once
#include "appframe.h"
namespace Flavor {
	using AppFrame::InputManager;
	class MessageLog: public AppFrame::UICanvas
	{
	public:
		MessageLog();
		void Init();
		void Terminate();
		void Update(InputManager& input, float deltaSeconds);
		void Render();
	};
}