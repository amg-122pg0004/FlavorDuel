/*****************************************************************//**
 * \file   AABBCollisionComponent.cpp
 * \brief  AABB(���[���h���W���ɉ��������`��)�R���W����
 *
 * \author �y�������Y
 * \date   April 2023
 *********************************************************************/
#pragma once
#include "AABBCollisionComponent.h"
#include <array>
#include "AppFrameMath.h"
#include "MV1Component.h"
#include "ObjectBase.h"
#include "Color.h"
namespace AppFrame {


    bool AABBCollisionComponent::Init()
    {
        return false;
    }

    void AABBCollisionComponent::Update(InputManager& input)
    {
    }

    void AABBCollisionComponent::Render()
    {
    }

    void AABBCollisionComponent::Debug() {
        VECTOR min = VSub(GetPosition(), _size);
        VECTOR max = VAdd(GetPosition(), _size);

        std::array<VECTOR, 8> boxVertex;
        boxVertex[0] = { min.x, min.y, min.z };
        boxVertex[1] = { min.x, max.y, min.z };
        boxVertex[2] = { min.x, min.y, max.z };
        boxVertex[3] = { min.x, max.y, max.z };
        boxVertex[4] = { max.x, min.y, min.z };
        boxVertex[5] = { max.x, max.y, min.z };
        boxVertex[6] = { max.x, min.y, max.z };
        boxVertex[7] = { max.x, max.y, max.z };

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
    VECTOR AABBCollisionComponent::GetPosition()
    {
        VECTOR position = _parent->GetPosition();

        if (_attachFrame > -1) {
            auto handle = _parent->GetComponent<MV1Component>()->GetModelHandle();
            auto matrix = MV1GetFrameLocalWorldMatrix(handle, _attachFrame);
            VECTOR position = VAdd(VTransform(Math::VZero(), matrix), _offset);
        }

        return VAdd(position, _offset);
    }
}