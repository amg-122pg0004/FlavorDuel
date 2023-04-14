/*****************************************************************//**
 * \file   SpehreCollisionComponent.h
 * \brief  球状コリジョン
 * 
 * \author 土居将太郎
 * \date   April 2023
 *********************************************************************/
#pragma once
#include "Object/ComponentBase.h"
namespace AppFrame {
	class  CollisionComponent :public ComponentBase
	{
	public:
		CollisionComponent();
		~CollisionComponent();
		bool Init()override;
		void Update(InputManager& input)override;
		void Render()override;
		void Debug()override;
		bool Intersect(CollisionComponent& otherCollision);
		bool Intersect(int mv1Handle);

		void SetRadius(float value, int index = 0) { _radius = value; }
		float GetRadius(int index = 0) { return _radius; }
		void SetAttachFrame(int value, int index = 0) { _attachFrame = value; }
		int GetAttachFrame(int index = 0) { return _attachFrame; }
		void SetOffset(VECTOR value, int index = 0) { _offset = value; }
		VECTOR GetOffset(int index = 0) { return _offset; }

		void AddSphere(float radius, VECTOR _offset = { 0.0f,0.0f,0.0f });
		void AddBox(VECTOR size, VECTOR _offset = { 0.0f,0.0f,0.0f });
		//first Mix second Max
		std::pair<VECTOR, VECTOR> GetAABB(int index = 0);
	private:
		bool IntersectSphere(int mv1Handle, int index = 0);
		// mv1がBox各辺のどれかに触れていたらtrue
		bool IntersectAABB(int mv1Handle, int index = 0);

		VECTOR _offset;//親オブジェクトのルート、あるいはアタッチボーンからの位置オフセット量
		float _radius;//球状コリジョンサイズ用
		int _attachFrame;//アタッチされているボーン
	};
}