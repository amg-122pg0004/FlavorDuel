#include "UITextBox.h"
#include "Color.h"
namespace AppFrame {
	namespace UI {
		TextBox::TextBox(std::string text)
			:_text{ text }
			, _font{ -1 }
			, _textColor{ Color::Red }
			, _drawBox{ false }
			, _boxColor{ Color::White }
			, _bind{ nullptr }
		{

		}

		TextBox::~TextBox()
		{
		}

		void TextBox::Update(InputManager& input, float deltaSecond)
		{
			if (_bind) {
				_text = _bind();
			}
		}

		void TextBox::Render()
		{
			auto aabb = this->GetAABB();
			if (_drawBox) {
				DrawBox(aabb.min.x, aabb.min.y, aabb.max.x, aabb.max.y, _boxColor, true);
			}
			if (this->GetAnchor() == Anchor::Center) {
				aabb.min += this->GetHalfSize();

				int textWidth = GetDrawStringWidth(_text.c_str(), static_cast<int>(_text.size()));
				if (_font != -1) {
					textWidth = GetDrawStringWidthToHandle(_text.c_str(), static_cast<int>(_text.size()), _font);
				}
				aabb.min.x -= static_cast<int>(static_cast<float>(textWidth) * 0.5f);

				int textHight{ GetFontSize() };
				if (_font != -1) {
					GetFontStateToHandle(nullptr, &textHight, nullptr, _font);
				}
				aabb.min.y -= static_cast<int>(static_cast<float>(textHight) * 0.5f);
			}

			if (_font == -1) {
				DrawString(aabb.min.x, aabb.min.y, _text.c_str(), _textColor);
			}
			else {
				DrawStringToHandle(aabb.min.x, aabb.min.y, _text.c_str(), _textColor, _font);
			}
		}
		void TextBox::SetBindFunction(std::function<std::string()> function)
		{
			this->SetNeedUpdate(true);
			_bind = function;
		}
	}
}