/*****************************************************************//**
 * \file   Easing.h
 * \brief  イージング関数を取得するクラス
 * 
 * \author 土居将太郎
 * \date   February 2023
 *********************************************************************/
#pragma once
#include <string>
#include <unordered_map>
#include <functional>
namespace AppFrame {
    using EasingMode = std::function<double(double, double, double, double)>;

    enum class EasingType {
        Linear,
        InQuad,
        OutQuad,
        InOutQuad,
        InCubic,
        OutCubic,
        InOutCubic,
        InQuart,
        OutQuart,
        InOutQuart,
        InQuint,
        OutQuint,
        InOutQuint,
        InSine,
        OutSine,
        InOutSine,
        InExpo,
        OutExpo,
        InOutExpo,
        InCirc,
        OutCirc,
        InOutCirc
    };
    using EasingMap = std::unordered_map<EasingType, EasingMode>;

    class Easing {
    public:
        // イージング関数のラムダを取得する
        static EasingMode GetMode(const EasingType type) {
            return _modes.at(type);
        }
    private:
        static const EasingMap _modes;
    };
}