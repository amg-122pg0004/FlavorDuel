#include "UIBox.h"
#include "Color.h"
using namespace AppFrame::UI;

Box::Box()
	:_color{ AppFrame::Color::White }
	, _fill{ true }
{
}

Box::~Box()
{
}

void Box::Update(InputManager& input, float deltaSecond)
{
}

void Box::Render()
{
	auto aabb = this->GetAABB();
	DrawBox(aabb.min.x, aabb.min.y, aabb.max.x, aabb.max.y, _color, _fill);
}
