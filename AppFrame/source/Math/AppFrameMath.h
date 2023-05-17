/*****************************************************************//**
 * \file   AppFrameMath.h
 * \brief  �ėp�I�Ȍv�Z�N���X
 * 
 * \author �y�������Y
 * \date   April 2023
 *********************************************************************/
#pragma once
#include <DxLib.h>
#include <cmath>
#include <iostream>
#include <random>
namespace AppFrame {

    namespace Math {
        // �~����
        constexpr float Pi = 3.1415926535f;
        constexpr float TwoPi = Pi * 2.0f;
        constexpr float PiOver2 = Pi / 2.0f;

        // �x������Ǔx(���W�A��)�ɕϊ�
        inline float ToRadians(float degrees) {
            return degrees * Pi / 180.0f;
        }
        // �Ǔx����x��(�f�B�O���[)�ɕϊ�
        inline float ToDegrees(float radians) {
            return radians * 180.0f / Pi;
        }
        // ��̒l�̑傫���l���擾
        template <typename T>
        T Max(const T& a, const T& b) {
            return (a < b ? b : a);
        }
        // ��̒l�̏������l���擾
        template <typename T>
        T Min(const T& a, const T& b) {
            return (a < b ? a : b);
        }
        // ��̒l�̊ԂŃN�����v����
        template <typename T>
        T Clamp(const T& value, const T& lower, const T& upper) {
            return Min(upper, Max(lower, value));
        }
        // ��̒l�̊ԂŃN�����v����
        template <typename T>
        bool Clamp2(T& value, const T& lower, const T& upper) {
            T oldValue = value;
            value = Min(upper, Max(lower, value));

            if (oldValue == value)
            {
                return false;
            }

            return true;
        }

        inline VECTOR VECTORClamp(VECTOR v, float min, float max)
        {
            v = { Clamp(v.x, min, max), Clamp(v.y, min, max), Clamp(v.z, min, max) };
            return v;
        }

        inline bool VECTORClamp2(VECTOR v, float min, float max)
        {
            if (Clamp2(v.x, min, max) || Clamp2(v.y, min, max) || Clamp2(v.z, min, max))
            {
                return true;
            }

            return false;
        }

        //���R����Ԃ���]�Z
        template <typename T>
        inline T Modulo(T n, T modulo) {
            if (n < 0) {
                n += modulo;
            }

            return n % modulo;
        }


        inline VECTOR VZero()
        {
            return { 0.0f, 0.0f, 0.0f };
        }

        inline VECTOR VUp()
        {
            return { 0.0f, 1.0f, 0.0f };
        }

        inline VECTOR VForward()
        {
            return { 0.0f, 0.0f, -1.0f };
        }

        inline VECTOR VRight()
        {
            return { 1.0f, 0.0f, 0.0f };
        }

        //���ς̂Ȃ��p��deg�ŕԂ�
        inline float VDot2Deg(VECTOR v1, VECTOR v2) {
            float vd = VDot(v1, v2);
            float absv = VSize(v1) * VSize(v2);
            return ToDegrees(std::acos(vd / absv));
        }
        //���`���
        inline VECTOR Lerp(VECTOR start, VECTOR end, float lerpParam) {
            lerpParam = Clamp(lerpParam, 0.0f, 1.0f);
            return  VAdd(start, VScale(VSub(end, start), lerpParam));
        }

        //���ς̂Ȃ��p��rad�ŕԂ�
        inline float VDot2Rad(VECTOR v1, VECTOR v2) {
            float vd = VDot(v1, v2);
            float absv = VSize(v1) * VSize(v2);
            return std::acos(vd / absv);
        }

        //���ʐ��`���//(�n�_�A�I�_�A��]�̒��S�_�A���݂̈ʒu�p�����[�^�[)
        //���K���x�N�g���n�_�I�_�̕��s���ƌ��݂̈ʒu�A���S�_���W���畽�s�l�ӌ`���쐬��
        //����𕪊������O�p�`�i���K���x�N�g���Ȃ̂ň�ӂ̑傫����1)�̓�ӂ����Ԃ��擾�B
        //������ӂ����Z���Č��݈ʒu���W���Ԃ���
        //a���ő�p�Ab���n�_�Ac�����݈ʒu���ꂼ��̊p�ɑΉ������ӂƂ���
        inline VECTOR SLerp(VECTOR start, VECTOR end, VECTOR center, float parameter) {
            parameter = Clamp(parameter, 0.0f, 1.0f);
            VECTOR s = VSub(start, center);
            VECTOR e = VSub(end, center);
            float dot = VDot2Rad(s, e);//���ς̂Ȃ��prad
            float aTheta = Math::ToRadians(180) - dot;
            //�p�x��a�ӂ̒������킩�����̂Ő����藝�Ŏn�_�I�_�ɕ��s�Ȓ����̕�ԍ��W�����Z�����K�����ꂽ���݈ʒu���W���擾
            VECTOR c = VScale(VNorm(e), sin(dot * parameter) / sin(aTheta));
            VECTOR b = VScale(VNorm(s), sin(dot * (1 - parameter)) / sin(aTheta));
            VECTOR a = VAdd(b, c);
            //��Ԃ��ꂽ���W���n�_�I�_�Ԃ̐��`��Ԃł��낦��
            float lerp = VSize(VScale(s, parameter)) + VSize(VScale(e, (1 - parameter)));
            return VAdd(start, VScale(a, lerp));
        }

        //�x�N�^�[2�_�Ԃ̋����̑傫����Ԃ�
        inline float DistanceV2V(VECTOR one, VECTOR two) {
            return VSize(VSub(one, two));
        }
        //�x�N�^�[2�_�ԋ����̑傫���̐�Βl�ŕԂ�
        inline float AbsDistanceV2V(VECTOR one, VECTOR two) {
            return fabs(DistanceV2V(one, two));
        }
        //���˃x�N�g����Ԃ��i�i�s�����x�N�g���A�ʂ̖@���x�N�g��)
        inline VECTOR Reflection(VECTOR forward, VECTOR normalLine) {
            float dot = VDot(VScale(forward, -1.0f), normalLine);
            VECTOR reflection = VScale(normalLine, dot * 2.0f);
            return VAdd(forward, reflection);
        }
        /**
         * ����̌��̒l���擾����
         *
         * \param value �擾���������l
         * \param digit �擾��������
         * \return ����̌��̒l�A�G���[�̎�-1
         */
        inline int GetDigitNumber(int value, int digit) {
            if (digit == 1) { return value % (static_cast<int>(std::pow(10, digit))); }

            int a = value % (static_cast<int>(std::pow(10, digit)));
            int b = value % static_cast<int>(std::pow(10, digit - 1));
            return static_cast<int>((a - b) / static_cast<int>(std::pow(10, digit - 1)));
        }
        //�s�񂩂�I�C���[�p�̒��o
        inline VECTOR RotationMatrix2Euler(MATRIX rotationMatrix) {
            float x = atan2(rotationMatrix.m[1][2], rotationMatrix.m[2][2]);
            float y = -asin(-rotationMatrix.m[0][2]);
            float z = atan2(rotationMatrix.m[0][1], rotationMatrix.m[0][0]);
            return{ x, y, z };
        }
    };

}