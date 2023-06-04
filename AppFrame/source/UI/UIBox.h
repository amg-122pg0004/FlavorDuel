/*****************************************************************//**
 * \file   UIBox.h
 * \brief  �{�b�N�X��`�悷�邾����UI�I�u�W�F�N�g
 *
 * \author �y�������Y
 * \date   May 2023
 *********************************************************************/
#pragma once
#include "UIObjectBase.h"
namespace AppFrame {
	namespace UI {
		class Box : public UIObjectBase
		{
		public:
			Box();
			~Box();
			void Update(InputManager& input, float deltaSecond)override;
			void Render()override;

			void SetColor(unsigned int color) { _color = color; }
			unsigned int GetColor() { return _color; }

			void SetFill(bool flag) { _fill = flag; }
			bool GetFill() { return _fill; }
		private:
			unsigned int _color;
			bool _fill;
		};
	}
}
