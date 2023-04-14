#include "UIImage.h"
#include "ImageServer.h"
namespace AppFrame {
	namespace UI {
		Image::Image(std::string path)
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
		}

		void Image::Render()
		{
			auto aabb = GetAABB();

			DrawExtendGraph(aabb.min.x, aabb.min.y, aabb.max.x, aabb.max.y, _image, true);
		}
		void Image::SetScale(float scale)
		{
			float sizeX = static_cast<float>(this->GetSize().x) * scale;
			float sizeY = static_cast<float>(this->GetSize().y) * scale;
			VECTOR2<int> setSize = { static_cast<int>(sizeX) ,static_cast<int>(sizeY) };
			this->SetSize(setSize);
		}
	}
}