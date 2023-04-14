#include "UIObjectBase.h"
namespace AppFrame {
	UIObjectBase::UIObjectBase()
		:_needUpdatePerFrame{ false }
		, _position{ 0,0 }
		, _size{ 100,70 }
		, _anchor{ Anchor::UpperLeft }
	{
	}

	UIObjectBase::~UIObjectBase()
	{
	}

	const VECTOR2<int> UIObjectBase::GetHalfSize()
	{
		float sizeX = static_cast<float>(this->GetSize().x) * 0.5f;
		float sizeY = static_cast<float>(this->GetSize().y) * 0.5f;
		return { static_cast<int>(sizeX),static_cast<int>(sizeY) };
	}

	const AABB2D<int> UIObjectBase::GetAABB()
	{
		//aabbçÏê¨
		VECTOR2<int> min = this->GetPosition();
		VECTOR2<int> max = min + this->GetSize();
		if (this->GetAnchor() == Anchor::Center) {
			VECTOR2<int> halfSize = this->GetHalfSize();
			min -= halfSize;
			max -= halfSize;
		}
		return { min, max };
	}
}