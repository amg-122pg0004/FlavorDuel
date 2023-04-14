/*****************************************************************//**
 * \file   CollisionComponent.h
 * \brief  球状コリジョン、AABBコリジョン
 *
 * \author 土居将太郎
 * \date   December 2022
 *********************************************************************/
#pragma once
#include "Object/ComponentBase.h"
namespace AppFrame {
	class  CollisionComponent :public ComponentBase
	{
	public:
		enum class Type {
			Sphere,
			AABB
		};
		CollisionComponent();
		~CollisionComponent();
		bool Init()override;
		void Update(InputManager& input)override;
		void Render()override;
		void Debug()override;
		bool Intersect(CollisionComponent& otherCollision, int selfIndex = 0, int otherIndex = 0);
		bool Intersect(int mv1Handle, int index = 0);

		void SetPosition(VECTOR value, int index = 0) { _params[index]._position = value; }
		VECTOR GetPosition(int index = 0) { return _params[index]._position; }
		void SetRadius(float value, int index = 0) { _params[index]._radius = value; }
		float GetRadius(int index = 0) { return _params[index]._radius; }
		void SetAttachFrame(int value, int index = 0) { _params[index]._attachFrame = value; }
		int GetAttachFrame(int index = 0) { return _params[index]._attachFrame; }
		void SetType(Type type, int index = 0) { _params[index]._type = type; }
		Type GetType(int index = 0) { return _params[index]._type; }
		void SetSize(VECTOR value, int index = 0) { _params[index]._size = value; }
		VECTOR GetSize(int index = 0) { return _params[index]._size; }
		void SetOffset(VECTOR value, int index = 0) { _params[index]._offset = value; }
		VECTOR GetOffset(int index = 0) { return _params[index]._offset; }

		void AddSphere(float radius, VECTOR _offset = { 0.0f,0.0f,0.0f });
		void AddBox(VECTOR size, VECTOR _offset = { 0.0f,0.0f,0.0f });
		//first Mix second Max
		std::pair<VECTOR, VECTOR> GetAABB(int index = 0);
	private:
		bool IntersectSphere(int mv1Handle, int index = 0);
		// mv1がBox各辺のどれかに触れていたらtrue
		bool IntersectAABB(int mv1Handle, int index = 0);

		struct Params {
			Type _type;//形状
			VECTOR _offset;//親オブジェクトのルート、あるいはアタッチボーンからの位置オフセット量
			VECTOR _position;
			float _radius;//球状コリジョンサイズ用
			VECTOR _size;//箱状コリジョンサイズ用
			int _attachFrame;//アタッチされているフレーム（ボーンの別称）
		};
		std::vector<Params> _params;
	};
}