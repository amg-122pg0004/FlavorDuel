/*****************************************************************//**
 * \file   ChangeScreen.cpp
 * \brief  �`��X�N���[��(�t���[���o�b�t�@)��ύX����ہADX���C�u�����̎d�l�Ƃ��ăJ������񂪃��Z�b�g����Ă��܂�����
 *         �����p�����߂ɍ쐬�����N���X
 *
 * \author �y�������Y
 * \date   February 2023
 *********************************************************************/
#include "ChangeScreen.h"
namespace AppFrame {
    void ChangeScreen::ChangeScreenAndSaveCamera(unsigned int screen)
    {
        auto camera = GetCameraParam();
        SetDrawScreen(screen);
        SetCameraParam(camera);
        return;
    }
}