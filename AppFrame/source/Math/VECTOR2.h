/*****************************************************************//**
 * \file   VECTOR2.h
 * \brief  2D�x�N�g���N���X
 * 
 * \author �y�������Y
 * \date   April 2023
 *********************************************************************/
#pragma once
namespace AppFrame {
    // 2D�x�N�g���N���X
    template<typename T>
    class VECTOR2 {
    public:
        // x����,y����
        T x, y;
        // �R���X�g���N�^
        VECTOR2() noexcept = default;
        constexpr VECTOR2(T inX, T inY) noexcept
            : x{ inX }
            , y{ inY } {
        }
        // �x�N�g���̉��Z a + b ���O���֐�
        friend bool operator==(const VECTOR2& a, const VECTOR2& b) {
            if (a.x == b.x && a.y == b.y) {
                return true;
            }
            else {
                return false;
            }
        }
        // �x�N�g���̉��Z a + b ���O���֐�
        friend VECTOR2 operator+(const VECTOR2& a, const VECTOR2& b) {
            return { a.x + b.x, a.y + b.y };
        }
        // �x�N�g���̌��Z a - b ���O���֐�
        friend VECTOR2 operator-(const VECTOR2& a, const VECTOR2& b) {
            return { a.x - b.x, a.y - b.y };
        }
        // �x�N�g���̃X�J���[�{ v * scalar ���O���֐�
        friend VECTOR2 operator*(const VECTOR2& v, T scalar) {
            return { v.x * scalar, v.y * scalar };
        }
        // �x�N�g���̃X�J���[�{ scalar * v ���O���֐�
        friend VECTOR2 operator*(T scalar, const VECTOR2& v) {
            return { v.x * scalar, v.y * scalar };
        }

        // �x�N�g���̃X�J���[���Z scalar * v ���O���֐�
        friend VECTOR2 operator/(const VECTOR2& v, T scalar) {
            return { v.x / scalar, v.y / scalar };
        }
        // �x�N�g�����Z���
        VECTOR2& operator+=(const VECTOR2& right) {
            x += right.x;
            y += right.y;
            return *this;
        }
        // �x�N�g�����Z���
        VECTOR2& operator-=(const VECTOR2& right) {
            x -= right.x;
            y -= right.y;
            return *this;
        }
        // �x�N�g���̃X�J����Z���
        VECTOR2& operator*=(double scalar) {
            x *= scalar;
            y *= scalar;
            return *this;
        }
    };
}
