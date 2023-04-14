/*****************************************************************//**
 * \file   CollisionComponent.cpp
 * \brief  球状コリジョン、AABBコリジョン
 *
 * \author 土居将太郎
 * \date   December 2022
 *********************************************************************/

#include "CollisionComponent.h"
#include "MV1Component.h"
#include "ObjectBase.h"
#include "Color.h"
namespace AppFrame {
	CollisionComponent::CollisionComponent()
	{
		_params.resize(1);
		_params[0]._type = Type::Sphere;
		_params[0]._offset = { 0.0f,0.0f,0.0f };
		_params[0]._position = { 0.0f,0.0f,0.0f };
		_params[0]._radius = { 10.0f };
		_params[0]._size = { 10.0f,10.0f,10.0f };
		_params[0]._attachFrame = -1;
	}

	CollisionComponent::~CollisionComponent()
	{
	}

	bool CollisionComponent::Init()
	{
		for (auto&& param : _params) {
			param._position = _parent->GetPosition();
		}
		return true;
	}

	void CollisionComponent::Update(InputManager& input)
	{
		for (int i = 0; i < _params.size(); ++i) {
			if (_params[i]._attachFrame > -1) {
				if (_parent->GetComponent<MV1Component>() != nullptr) {
					auto handle = _parent->GetComponent<MV1Component>()->GetModelHandle();
					auto matrix = MV1GetFrameLocalWorldMatrix(handle, _params[i]._attachFrame);
					_params[i]._position = VAdd(VTransform({ 0,0,0 }, matrix), _params[i]._offset);
					continue;
				}
			}
			_params[i]._position = VAdd(_parent->GetPosition(), _params[i]._offset);
		}
	}

	void CollisionComponent::Render()
	{
	}

	void CollisionComponent::Debug()
	{
		for (int i = 0; i < _params.size(); ++i) {
			if (_params[i]._type == Type::AABB) {
				auto min = GetAABB(i).first;
				auto max = GetAABB(i).second;

				std::array<VECTOR, 8> boxVertex = { 0.0f,0.0f,0.0f };
				boxVertex[0] = { min.x, min.y, min.z };
				boxVertex[1] = { min.x,max.y,min.z };
				boxVertex[2] = { min.x,min.y,max.z };
				boxVertex[3] = { min.x,max.y,max.z };
				boxVertex[4] = { max.x,min.y,min.z };
				boxVertex[5] = { max.x,max.y,min.z };
				boxVertex[6] = { max.x,min.y,max.z };
				boxVertex[7] = { max.x,max.y,max.z };
				std::array<VECTOR2<int>, 12> boxLines;
				boxLines[0] = { 0, 1 };
				boxLines[1] = { 0, 2 };
				boxLines[2] = { 0, 4 };
				boxLines[3] = { 3, 1 };
				boxLines[4] = { 3, 2 };
				boxLines[5] = { 3, 7 };
				boxLines[6] = { 5, 1 };
				boxLines[7] = { 5, 4 };
				boxLines[8] = { 5, 7 };
				boxLines[9] = { 6, 2 };
				boxLines[10] = { 6, 4 };
				boxLines[11] = { 6, 7 };


				for (int line = 0; line < 12; ++line) {
					DrawLine3D(boxVertex[boxLines[line].x], boxVertex[boxLines[line].y], Color::Red);
				}
			}
			if (_params[i]._type == Type::Sphere) {
				DrawSphere3D(_params[i]._position, _params[i]._radius, 12, Color::Yellow, Color::Black, false);
			}
		}
	}

	bool CollisionComponent::Intersect(CollisionComponent& otherCollision, int selfIndex, int otherIndex)
	{
		if (_params[selfIndex]._type == Type::Sphere && otherCollision.GetType(otherIndex) == Type::Sphere) {
			auto dif = VSub(otherCollision.GetPosition(otherIndex), _params[selfIndex]._position);
			auto otherRadius = otherCollision.GetRadius(otherIndex);
			return dif.x * dif.x + dif.y * dif.y + dif.z * dif.z <= (_params[selfIndex]._radius + otherRadius) * (_params[selfIndex]._radius + otherRadius);
		}
		if (_params[selfIndex]._type == Type::AABB && otherCollision.GetType(otherIndex) == Type::AABB) {
			auto selfMin = GetAABB(selfIndex).first;
			auto selfMax = GetAABB(selfIndex).second;
			auto otherMin = otherCollision.GetAABB(otherIndex).first;
			auto otherMax = otherCollision.GetAABB(otherIndex).second;
			return (selfMin.x <= otherMax.x && selfMax.x >= otherMin.x) &&
				(selfMin.y <= otherMax.y && selfMax.y >= otherMin.y) &&
				(selfMin.z <= otherMax.z && selfMax.z >= otherMin.z);
		}
		if (_params[selfIndex]._type == Type::Sphere && otherCollision.GetType() == Type::AABB) {
			auto otherMin = otherCollision.GetAABB(otherIndex).first;
			auto otherMax = otherCollision.GetAABB(otherIndex).second;
			auto direction = VNorm(VSub(otherCollision.GetPosition(otherIndex), _params[selfIndex]._position));
			auto nearPoint = VAdd(_params[selfIndex]._position, VScale(direction, _params[selfIndex]._radius));
			return (nearPoint.x >= otherMin.x && nearPoint.x <= otherMax.x) &&
				(nearPoint.y >= otherMin.y && nearPoint.y <= otherMax.y) &&
				(nearPoint.z >= otherMin.z && nearPoint.z <= otherMax.z);
		}
		if (_params[selfIndex]._type == Type::AABB && otherCollision.GetType(otherIndex) == Type::Sphere) {
			auto selfMin = GetAABB(selfIndex).first;
			auto selfMax = GetAABB(selfIndex).second;
			auto direction = VNorm(VSub(_params[selfIndex]._position, otherCollision.GetPosition(otherIndex)));
			auto nearPoint = VAdd(otherCollision.GetPosition(otherIndex), VScale(direction, otherCollision.GetRadius(otherIndex)));
			if ((nearPoint.x >= selfMin.x && nearPoint.x <= selfMax.x) &&
				(nearPoint.y >= selfMin.y && nearPoint.y <= selfMax.y) &&
				(nearPoint.z >= selfMin.z && nearPoint.z <= selfMax.z)) {
				return true;
			}
		}
		return false;
	}

	bool CollisionComponent::Intersect(int mv1Handle, int index)
	{
		switch (_params[index]._type)
		{
		case CollisionComponent::Type::Sphere:
			return IntersectSphere(mv1Handle);
		case CollisionComponent::Type::AABB:
			return IntersectAABB(mv1Handle);
		default:
			return false;
		}
	}

	void CollisionComponent::AddSphere(float radius, VECTOR offset)
	{
		Params param;
		param._type = Type::Sphere;
		param._offset = offset;
		param._position = { 0.0f,0.0f,0.0f };
		param._radius = radius;
		param._size = { 0.0f,0.0f,0.0f };
		param._attachFrame = -1;
		_params.push_back(param);
	}

	void CollisionComponent::AddBox(VECTOR size, VECTOR offset)
	{
		Params param;
		param._type = Type::AABB;
		param._offset = offset;
		param._position = { 0.0f,0.0f,0.0f };
		param._radius = 0.0f;
		param._size = size;
		param._attachFrame = -1;
		_params.push_back(param);
	}

	bool CollisionComponent::IntersectSphere(int mv1Handle, int index)
	{
		MV1SetupCollInfo(mv1Handle, -1);
		auto hitResult = MV1CollCheck_Sphere(mv1Handle, -1, _params[index]._position, _params[index]._radius);
		bool result{ false };
		if (hitResult.HitNum > 0) {
			result = true;
		}
		MV1CollResultPolyDimTerminate(hitResult);
		return result;
	}

	bool CollisionComponent::IntersectAABB(int mv1Handle, int index)
	{
		MV1SetupCollInfo(mv1Handle, -1);
		auto min = GetAABB(index).first;
		auto max = GetAABB(index).second;

		std::array<VECTOR, 8> boxVertex = { 0.0f,0.0f,0.0f };
		boxVertex[0] = { min.x,min.y,min.z };
		boxVertex[1] = { min.x,max.y,min.z };
		boxVertex[2] = { min.x,min.y,max.z };
		boxVertex[3] = { min.x,max.y,max.z };
		boxVertex[4] = { max.x,min.y,min.z };
		boxVertex[5] = { max.x,max.y,min.z };
		boxVertex[6] = { max.x,min.y,max.z };
		boxVertex[7] = { max.x,max.y,max.z };
		std::array<VECTOR, 12> boxLines = { 0.0f,0.0f,0.0f };
		boxLines[0] = VSub(boxVertex[0], boxVertex[1]);
		boxLines[1] = VSub(boxVertex[0], boxVertex[2]);
		boxLines[2] = VSub(boxVertex[0], boxVertex[4]);
		boxLines[3] = VSub(boxVertex[3], boxVertex[1]);
		boxLines[4] = VSub(boxVertex[3], boxVertex[2]);
		boxLines[5] = VSub(boxVertex[3], boxVertex[7]);
		boxLines[6] = VSub(boxVertex[5], boxVertex[1]);
		boxLines[7] = VSub(boxVertex[5], boxVertex[4]);
		boxLines[8] = VSub(boxVertex[5], boxVertex[7]);
		boxLines[9] = VSub(boxVertex[6], boxVertex[2]);
		boxLines[10] = VSub(boxVertex[6], boxVertex[4]);
		boxLines[11] = VSub(boxVertex[6], boxVertex[7]);

		bool result{ false };
		for (int i = 0; i < 12; ++i) {
			auto hitResult = MV1CollCheck_Line(mv1Handle, -1, _params[index]._position, boxLines[i]);
			if (hitResult.HitFlag > 0) {
				result = true;
				break;
			}
		}
		return result;
	}

	std::pair<VECTOR, VECTOR> CollisionComponent::GetAABB(int index) {

		VECTOR max = VScale(_params[index]._size, 0.5f);
		max = VAdd(max, _params[index]._offset);
		max = VTransform(max, _parent->GetRotationMatrix());
		max = VAdd(max, _parent->GetPosition());
		VECTOR min = VScale(_params[index]._size, -0.5f);
		min = VAdd(min, _params[index]._offset);
		min = VTransform(min, _parent->GetRotationMatrix());
		min = VAdd(min, _parent->GetPosition());
		VECTOR resultMin = min;
		VECTOR resultMax = max;
		if (max.x < min.x) {
			resultMin.x = max.x;
			resultMax.x = min.x;
		}
		if (max.y < min.y) {
			resultMin.y = max.y;
			resultMax.y = min.y;
		}
		if (max.z < min.z) {
			resultMin.z = max.z;
			resultMax.z = min.z;
		}
		return { resultMin,resultMax };
	}
}