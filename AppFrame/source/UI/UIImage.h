/*****************************************************************//**
 * \file   UIButton.cpp
 * \brief  画像を表示するUIオブジェクト
 *
 * \author 土居将太郎
 * \date   April 2023
 *********************************************************************/
#pragma once
#include <string>
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

            void SetScale(float scale);
        private:
            int _image;
        };
    }
}