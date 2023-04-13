/*****************************************************************//**
 * \file   AABBComponent.h
 * \brief  親オブジェクトに追従する2DのAABB
 *
 * \author 土居将太郎
 * \date   November 2022
 *********************************************************************/
#pragma once
#include "ComponentBase.h"
#include "../Utility/AABB2D.h"
namespace AppFrame {
    class AABB2DComponent :public ComponentBase
    {
    public:
        AABB2DComponent();
        ~AABB2DComponent();
        bool Init()override;
        void Update(InputManager& input)override;
        void Render()override;
        void Debug()override;
        void SetSizeX(float sizex) { _sizeX = sizex; }
        void SetSizeY(float sizez) { _sizeY = sizez; }
        AABB<float> GetAABB() { return _collision; }
        //毎フレームの位置更新を行うか
        void SetMovable(bool flag) { _movable = flag; }
        void SetXZaxis(bool flag) { _XZaxis = flag; };
    private:
        void UpdateCollision();
        bool _movable;
        float _sizeX, _sizeY;
        AABB<float> _collision;
        bool _rootPositionCenter;
        bool _XZaxis;
    };
}
