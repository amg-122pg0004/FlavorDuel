/*****************************************************************//**
 * \file   UIBox.h
 * \brief  ボックスを描画するだけのUIオブジェクト
 *
 * \author 土居将太郎
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
