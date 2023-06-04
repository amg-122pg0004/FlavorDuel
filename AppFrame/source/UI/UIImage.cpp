#include "UIImage.h"
#include "ImageServer.h"
using namespace AppFrame::UI;

Image::Image(std::string path) 
	:_angle{ 0.0f }
	, _update{ nullptr }
	, _scale{ 1.0f }
	, _transparent{ true }
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
	if (!(this->GetVisible())) {
		return;
	}
	VECTOR2<int> renderPosition {this->GetPosition()};
	if (this->GetAnchor() == Anchor::UpperLeft) {
		VECTOR2<int> half = GetHalfSize();
		half = { static_cast<int>(static_cast<float>(half.x) * _scale), static_cast<int>(static_cast<float>(half.y) * _scale) };
		renderPosition += half;
	}
	DrawRotaGraph(renderPosition.x, renderPosition.y, _scale, _angle, _image, _transparent);
}