/*****************************************************************//**
 * \file   CollisionComponentBase.h
 * \brief  コリジョンコンポーネントを一括管理する為に作成した基底クラス
 *         
 * 
 * \author 土居将太郎
 * \date   April 2023
 *********************************************************************/
#pragma once
#include "CollisionComponent.h"
#include "ComponentBase.h"
namespace AppFrame {
	class SphereCollisionComponent;
	class AABBCollitionComponent;

	class CollisionComponentBase : public ComponentBase
	{
		virtual bool Init();
		virtual void Update(InputManager& input);
		virtual void Render();
		virtual void Debug();

		virtual bool Hit(SphereCollisionComponent& sphere) = 0;
		virtual bool Hit(AABBCollitionComponent& aabb) = 0;
		virtual bool Hit(int& mv1Handle) = 0;
	};
}


