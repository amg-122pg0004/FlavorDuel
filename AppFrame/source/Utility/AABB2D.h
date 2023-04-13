/*****************************************************************//**
 * \file   AABB2D.h
 * \brief  2D��AABB�N���X
 *
 * \author �y�������Y
 * \date   November 2022
 *********************************************************************/
#pragma once
#include <DxLib.h>
#include "../AppFrameMath.h"
namespace AppFrame {
    template<typename T>
    class AABB {
    public:
        VECTOR2<T> min;//<�R���W������`�̍�����W
        VECTOR2<T> max;//<�R���W������`�̉E�����W

    };
    /**
    * \brief 2��AABB�̌�������
    *
    * \param r1 AABB1��
    * \param r2 AABB2��
    * \return �������Ă�����True
    */
    template<typename T>
    bool Intersect(const AABB<T>& r1, const AABB<T>& r2);

    /**
    * \brief 2��AABB�̌�������
    *
    * \param r1 AABB1��
    * \param r2 AABB2��
    * \return 1�ڂ̒���2�ڂ����S�Ɏ��܂��Ă����True
    */
    template<typename T>
    bool Within(const AABB<T>& r1, const AABB<T>& r2);

    /**
    * \brief 1��AABB��1�̓_�̌�������
    *
    * \param r1 AABB
    * \param r2 ���W
    * \return 1�ڂ̒���2�ڂ����܂��Ă����True
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