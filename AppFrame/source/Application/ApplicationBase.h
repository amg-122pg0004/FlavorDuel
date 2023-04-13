/*****************************************************************//**
 * \file   ApplicationBase.h
 * \brief  �A�v���P�[�V�����̊��N���X
 *         �p����̃O���[�o����ԂŎ��̂��쐬���Ďg�p����
 *         Input,Update,Render�����ԂɃ��C�����[�v�ŌĂ΂��
 *       �@Debug�͌p����Render���ŌĂяo���Ďg�p����z��
 * 
 * \author �y�������Y
 * \date   December 2022
 *********************************************************************/

#include "dxlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory>

namespace AppFrame {
    class ModeServer;
    class InputManager;
    class Vibration;

    class ApplicationBase
    {
    public:
        ApplicationBase();
        virtual ~ApplicationBase();

        virtual bool Initialize(HINSTANCE hInstance);
        virtual bool Terminate();
        virtual bool Input();
        virtual bool Update();
        virtual bool Render();
        virtual bool Debug();

        virtual bool AppWindowed() { return true; }
        virtual int DispSizeW() { return 640; }
        virtual int DispSizeH() { return 480; }

        static	ApplicationBase* GetInstance() { return _lpInstance; }

        virtual bool GetAppEnd() { return _appEnd; }
        virtual void SetAppEnd(bool flag) { _appEnd = flag; }
    private:
        static	ApplicationBase* _lpInstance;//�p�����this�|�C���^������
        std::unique_ptr<ModeServer> _modeServer;//���[�h�Ǘ��N���X
        std::unique_ptr<Vibration> _vibration;//�U���̃I���I�t�Ǘ�
        bool _appEnd;//�Q�[���I��h�t���O
    protected:
        std::unique_ptr<InputManager> _inputManager;//���͂��擾
    };
}
