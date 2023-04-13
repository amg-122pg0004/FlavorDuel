/*****************************************************************//**
 * \file   AABB2D.h
 * \brief  2DのAABBクラス
 *
 * \author 土居将太郎
 * \date   November 2022
 *********************************************************************/
#pragma once
#include <DxLib.h>
#include "../AppFrameMath.h"
namespace AppFrame {
    template<typename T>
    class AABB {
    public:
        VECTOR2<T> min;//<コリジョン矩形の左上座標
        VECTOR2<T> max;//<コリジョン矩形の右下座標

    };
    /**
    * \brief 2つのAABBの交差判定
    *
    * \param r1 AABB1個目
    * \param r2 AABB2個目
    * \return 交差していたらTrue
    */
    template<typename T>
    bool Intersect(const AABB<T>& r1, const AABB<T>& r2);

    /**
    * \brief 2つのAABBの交差判定
    *
    * \param r1 AABB1個目
    * \param r2 AABB2個目
    * \return 1個目の中に2個目が完全に収まっていればTrue
    */
    template<typename T>
    bool Within(const AABB<T>& r1, const AABB<T>& r2);

    /**
    * \brief 1つのAABBと1つの点の交差判定
    *
    * \param r1 AABB
    * \param r2 座標
    * \return 1個目の中に2個目が収まっていればTrue
    */
    template<typename T>
    bool Within(const AABB<T>& r1, const VECTOR2<T>& r2);

    template<typename T>
    bool Intersect(const AABB<T>& r1, const AABB<T>& r2)
    {
        if (r1.max.x < r2.min.x) {
            return false;
        }

        if (r2.max.x < r1.min.x) {
            return false;
        }

        if (r1.max.y < r2.min.y) {
            return false;
        }

        if (r2.max.y < r1.min.y) {
            return false;
        }

        return true;
    }
    template<typename T>
    bool Within(const AABB<T>& r1, const AABB<T>& r2)
    {
        if (r1.max.x < r2.max.x) {
            return false;
        }

        if (r1.min.x > r2.min.x) {
            return false;
        }

        if (r1.max.y < r2.max.y) {
            return false;
        }

        if (r1.min.y > r2.min.y) {
            return false;
        }

        return true;
    }
    template<typename T>
    bool Within(const AABB<T>& r1, const VECTOR2<T>& r2)
    {
        if (r1.max.x < r2.x) {
            return false;
        }

        if (r1.min.x > r2.x) {
            return false;
        }

        if (r1.max.y < r2.y) {
            return false;
        }

        if (r1.min.y > r2.y) {
            return false;
        }

        return true;
    }

    template<typename T, typename U>
    bool Within(const AABB<T>& r1, const VECTOR2<U>& r2)
    {
        if (r1.max.x < r2.x) {
            return false;
        }

        if (r1.min.x > r2.x) {
            return false;
        }

        if (r1.max.y < r2.y) {
            return false;
        }

        if (r1.min.y > r2.y) {
            return false;
        }

        return true;
    }
}