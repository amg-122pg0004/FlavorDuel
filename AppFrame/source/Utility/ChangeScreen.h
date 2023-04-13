/*****************************************************************//**
 * \file   ChangeScreen.h
 * \brief  �`��X�N���[��(�t���[���o�b�t�@)��ύX����ہADX���C�u�����̎d�l�Ƃ��ăJ������񂪃��Z�b�g����Ă��܂�����
 *         �����p�����߂ɍ쐬�����N���X
 * 
 * \author �y�������Y
 * \date   February 2023
 *********************************************************************/
#pragma once
#include <DxLib.h>
namespace AppFrame {
    class ChangeScreen
    {
    public:
        struct CameraParam {
            MATRIX transform;
            float Near;
            float Far;
            float Fov;
        };
        /**
         * \brief ���݂̃J���������擾����
         * \return �J������񂪓������\����
         */
        static inline CameraParam GetCameraParam() { return { GetCameraViewMatrix(), GetCameraNear(), GetCameraFar(), GetCameraFov() }; }

        /**
         * \brief �J��������ݒ肷��
         * \param param �J������񂪓������\����
         */
        static inline void SetCameraParam(CameraParam param) {
            SetCameraViewMatrix(param.transform);
            SetCameraNearFar(param.Near, param.Far);
            SetupCamera_Perspective(param.Fov);

        }
        /**
         * \brief �J���������ێ������܂ܕ`��X�N���[����؂�ւ���
         * \param screen �ύX����`��X�N���[��
         */
        static void ChangeScreenAndSaveCamera(unsigned int screen);
    };

}