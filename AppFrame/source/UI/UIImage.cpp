#include "UIImage.h"
#include "ImageServer.h"
namespace AppFrame {
	namespace UI {
		Image::Image(std::string path) :_angle{ 0.0f }, _update{ nullptr }
		{
			_image = ImageServer::LoadGraph(path);
			int sizeX{ 0 }, sizeY{ 0 };
			GetGraphSize(_image, &sizeX, &sizeY);
			this->SetSize({ sizeX,sizeY });
		}

		Image::~Image()
		{
		}

		void Image::Update(InputManager& input, float deltaSecond)
		{
			if (_update) {
				_update(*this);
			}
		}

		void Image::Render()
		{
			VECTOR2<int> renderPosition {this->GetPosition()};
			if (this->GetAnchor() == Anchor::UpperLeft) {
				renderPosition += GetHalfSize();
			}
			DrawRotaGraph(renderPosition.x, renderPosition.y, 1.0f, _angle, _image, true);
		}
	}
}