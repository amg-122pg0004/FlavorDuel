/*****************************************************************//**
 * \file   UIButton.cpp
 * \brief  画像を表示するUIオブジェクト
 *
 * \author 土居将太郎
 * \date   April 2023
 *********************************************************************/
#pragma once
#include <string>
#include <functional>
#include "UIObjectBase.h"

namespace AppFrame {
	namespace UI {
		class Image : public UIObjectBase
		{
		public:
			Image(std::string path);
			~Image();
			void Update(InputManager& input, float deltaSecond)override;
			void Render()override;

			void SetScale(float scale) { _scale = scale; }
			float getScale() { return _scale; }

			void SetAngle(float angle) { _angle = angle; }
			float GetAngle() { return _angle; }

			void SetUpdateFunction(std::function<void(Image& self)> function) { _update = function; }
		private:
			int _image;
			float _scale;
			float _angle;
			std::function<void(Image& self)> _update;
		};
	}
}