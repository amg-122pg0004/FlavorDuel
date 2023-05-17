/*****************************************************************//**
 * \file   Easing.cpp
 * \brief  �C�[�W���O�֐����擾����N���X
 *
 * \author �y�������Y
 * \date   February 2023
 *********************************************************************/
#include "Easing.h"
#include "AppFrameMath.h"
namespace AppFrame {

    /**
    * \brief �C�[�W���O�֐������_���e�[�u��
    * \param t �o�ߎ���
    * \param b �J�n�l
    * \param c �I���l
    * \param d ��������
    * \return �v�Z����
    */
    const EasingMap Easing::_modes = {
        {   EasingType::Linear,
            [](double t, double b, double c, double d) {
                return (c - b) * t / d + b;
            }
        },
        {   EasingType::InQuad,
            [](double t, double b, double c, double d) {
                t /= d;
                return (c - b) * t * t + b;
            }
        },
        {   EasingType::OutQuad,
            [](double t, double b, double c, double d) {
                t /= d;
                return -(c - b) * t * (t - 2) + b;
            }
        },
        {   EasingType::InOutQuad,
            [](double t, double b, double c, double d) {
                t /= d / 2.0;

                if (t < 1) {
                    return (c - b) / 2.0 * t * t + b;
                }

                t--;
                return -(c - b) / 2.0 * (t * (t - 2) - 1) + b;
            }
        },
        {   EasingType::InCubic,
            [](double t, double b, double c, double d) {
                t /= d;
                return (c - b) * t * t * t + b;
            }
        },
        {   EasingType::OutCubic,
            [](double t, double b, double c, double d) {
                t /= d;
                t--;
                return (c - b) * (t * t * t + 1) + b;
            }
        },
        {   EasingType::InOutCubic,
            [](double t, double b, double c, double d) {
                t /= d / 2.0;

                if (t < 1) {
                    return (c - b) / 2.0 * t * t * t + b;
                }

                t -= 2;
                return (c - b) / 2.0 * (t * t * t + 2) + b;
            }
        },
        {   EasingType::InQuart,
            [](double t, double b, double c, double d) {
                t /= d;
                return (c - b) * t * t * t * t + b;
            }
        },
        {   EasingType::OutQuart,
            [](double t, double b, double c, double d) {
                t /= d;
                t--;
                return -(c - b) * (t * t * t * t - 1) + b;
            }
        },
        {   EasingType::InOutQuart,
            [](double t, double b, double c, double d) {
                t /= d / 2.0;

                if (t < 1) {
                    return (c - b) / 2.0 * t * t * t * t + b;
                }

                t -= 2;
                return -(c - b) / 2.0 * (t * t * t * t - 2) + b;
            }
        },
        {   EasingType::InQuint,
            [](double t, double b, double c, double d) {
                t /= d;
                return (c - b) * t * t * t * t * t + b;
            }
        },
        {   EasingType::OutQuint,
            [](double t, double b, double c, double d) {
                t /= d;
                t--;
                return (c - b) * (t * t * t * t * t + 1) + b;
            }
        },
        {   EasingType::InOutQuint,
            [](double t, double b, double c, double d) {
                t /= d / 2.0;

                if (t < 1) {
                    return (c - b) / 2.0 * t * t * t * t * t + b;
                }

                t -= 2;
                return (c - b) / 2.0 * (t * t * t * t * t + 2) + b;
            }
        },
        {   EasingType::InSine,
            [](double t, double b, double c, double d) {
                return (c - b) * (1 - std::cos(t / d * (Math::PiOver2))) + b;
            }
        },
        {   EasingType::OutSine,
            [](double t, double b, double c, double d) {
                return (c - b) * std::sin(t / d * Math::PiOver2) + b;
            }
        },
        {   EasingType::InOutSine,
            [](double t, double b, double c, double d) {
                return -(c - b) / 2.0 * (std::cos(Math::Pi * t / d) - 1) + b;
            }
        },
        {   EasingType::InExpo,
            [](double t, double b, double c, double d) {
                return (c - b) * std::pow(2.0, 10 * (t / d - 1)) + b;
            }
        },
        {   EasingType::OutExpo,
            [](double t, double b, double c, double d) {
                return (c - b) * (-std::pow(2.0, -10 * t / d) + 1) + b;
            }
        },
        {   EasingType::InOutExpo,
            [](double t, double b, double c, double d) {
                t /= d / 2.0;

                if (t < 1) {
                    return (c - b) / 2.0 * std::pow(2.0, 10 * (t - 1)) + b;
                }

                t--;
                return (c - b) / 2.0 * (-std::pow(2.0, -10 * t) + 2) + b;
            }
        },
        {   EasingType::InCirc,
            [](double t, double b, double c, double d) {
                t /= d;
                return -(c - b) * (std::sqrt(1 - t * t) - 1) + b;
            }
        },
        {   EasingType::OutCirc,
            [](double t, double b, double c, double d) {
                t /= d;
                t--;
                return (c - b) * std::sqrt(1 - t * t) + b;
            }
        },
        {   EasingType::InOutCirc,
            [](double t, double b, double c, double d) {
                t /= d / 2.0;

                if (t < 1) {
                    return -(c - b) / 2.0 * (std::sqrt(1 - t * t) - 1) + b;
                }

                t -= 2;
                return (c - b) / 2.0 * (std::sqrt(1 - t * t) + 1) + b;
            }
        }
    };
}