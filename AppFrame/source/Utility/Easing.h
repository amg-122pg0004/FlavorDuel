/*****************************************************************//**
 * \file   Easing.h
 * \brief  �C�[�W���O�֐����擾����N���X
 * 
 * \author �y�������Y
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
        // �C�[�W���O�֐��̃����_���擾����
        static EasingMode GetMode(const EasingType type) {
            return _modes.at(type);
        }
    private:
        static const EasingMap _modes;
    };
}