/*****************************************************************//**
 * \file   VECTOR2.h
 * \brief  2Dベクトルクラス
 * 
 * \author 土居将太郎
 * \date   April 2023
 *********************************************************************/
#pragma once
namespace AppFrame {
    // 2Dベクトルクラス
    template<typename T>
    class VECTOR2 {
    public:
        // x成分,y成分
        T x, y;
        // コンストラクタ
        VECTOR2() noexcept = default;
        constexpr VECTOR2(T inX, T inY) noexcept
            : x{ inX }
            , y{ inY } {
        }
        // ベクトルの加算 a + b ※外部関数
        friend bool operator==(const VECTOR2& a, const VECTOR2& b) {
            if (a.x == b.x && a.y == b.y) {
                return true;
            }
            else {
                return false;
            }
        }
        // ベクトルの加算 a + b ※外部関数
        friend VECTOR2 operator+(const VECTOR2& a, const VECTOR2& b) {
            return { a.x + b.x, a.y + b.y };
        }
        // ベクトルの減算 a - b ※外部関数
        friend VECTOR2 operator-(const VECTOR2& a, const VECTOR2& b) {
            return { a.x - b.x, a.y - b.y };
        }
        // ベクトルのスカラー倍 v * scalar ※外部関数
        friend VECTOR2 operator*(const VECTOR2& v, T scalar) {
            return { v.x * scalar, v.y * scalar };
        }
        // ベクトルのスカラー倍 scalar * v ※外部関数
        friend VECTOR2 operator*(T scalar, const VECTOR2& v) {
            return { v.x * scalar, v.y * scalar };
        }

        // ベクトルのスカラー除算 scalar * v ※外部関数
        friend VECTOR2 operator/(const VECTOR2& v, T scalar) {
            return { v.x / scalar, v.y / scalar };
        }
        // ベクトル加算代入
        VECTOR2& operator+=(const VECTOR2& right) {
            x += right.x;
            y += right.y;
            return *this;
        }
        // ベクトル減算代入
        VECTOR2& operator-=(const VECTOR2& right) {
            x -= right.x;
            y -= right.y;
            return *this;
        }
        // ベクトルのスカラ乗算代入
        VECTOR2& operator*=(double scalar) {
            x *= scalar;
            y *= scalar;
            return *this;
        }
    };
}
