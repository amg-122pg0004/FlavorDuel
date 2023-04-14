#include "CollisionComponentBase.h"

namespace AppFrame {

	bool AppFrame::CollisionComponentBase::Init()
	{
		return false;
	}

	void AppFrame::CollisionComponentBase::Update(InputManager& input)
	{
	}

	void AppFrame::CollisionComponentBase::Render()
	{
	}

	void AppFrame::CollisionComponentBase::Debug()
	{
	}

	bool AppFrame::CollisionComponentBase::CheckIntersect(SphereCollisionComponent& sphere)
	{
		return false;
	}

	bool AppFrame::CollisionComponentBase::CheckIntersect(AABBCollitionComponent& aabb)
	{
		return false;
	}

	bool AppFrame::CollisionComponentBase::CheckIntersect(int& mv1Handle)
	{
		return false;
	}
}