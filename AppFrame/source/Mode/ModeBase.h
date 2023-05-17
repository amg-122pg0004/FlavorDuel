/*****************************************************************//**
 * \file   ModeBase.h
 * \brief  ���[�h�̊��N���X
 * 
 * \author �y�������Y
 * \date   April 2023
 *********************************************************************/
#pragma once
#include <memory>
#include <string>
namespace AppFrame {
    class InputManager;
    class BlurRenderer;
    class ModeServer;
    class ObjectServer;
    class UICanvasServer;

    class ModeBase
    {
    public:
        ModeBase();
        virtual ~ModeBase();

        virtual bool	Initialize();
        virtual bool	Terminate();
        virtual bool	Update(InputManager& input);
        virtual bool	Render();
        virtual bool	Debug();

        //���̃��[�h���n�܂��Ă���̃J�E���^
        int	GetModeCount() { return _cntMode; }
        //���̃��[�h���n�܂��Ă���̎���ms
        unsigned long GetModeTime() { return _tmMode; }
        //�O�t���[������̌o�ߎ���ms
        unsigned long GetStepTime()const { return _tmStep; }
        // ���t���[����1��Process()���ĂԂ�(def:1)
        void SetCallPerFrame(int frame) { _callPerFrame = _callPerFrame_cnt = frame; }
        // 1��̌Ăяo���ɉ���Process()���ĂԂ�(def:1)
        void SetCallOfCount(int count) { _callOfCount = count; }
        // ���t���[����1��Process()���ĂԂ�(def:1)
        int GetCallPerFrame() { return _callPerFrame; }
        // 1��̌Ăяo���ɉ���Process()���ĂԂ�(def:1)
        int GetCallOfCount() { return _callOfCount; }

        int GetLayer() { return _layer; }
        void SetLayer(int value) { _layer = value; }
        int GetUID() { return _uid; }
        void SetUID(int value) { _uid = value; }
        std::string GetName() { return _name; }
        void SetName(std::string string) { _name = string; }

        // ���Ԍo�߂�������
        void StepTime(unsigned long tmNow, float slowRate);
        // �J�E���g��i�߂�
        void StepCount();

        std::unique_ptr<ObjectServer>& GetObjectServer() { return _objectServer; }
        std::unique_ptr<BlurRenderer>& GetPostProcess() { return _blurRenderer; }
        //�u���[���g�p���邩
        bool GetBlurFlag() { return _blurActivate; }

        std::unique_ptr<UICanvasServer>& GetUICanvasServer() { return _uiCanvasServer; }

    private:
        // ModeServer�p
        std::string		_name;
        int				_uid;
        int				_layer;

        // ���[�h�������p
        int		_cntMode;	// �{���[�h�ɓ����Ă���̃J�E���^, 0�X�^�[�g
        unsigned long	_tmMode;	// �{���[�h�ɓ����Ă���̎��ԁBms
        unsigned long	_tmStep;	// �O�t���[������̌o�ߎ��ԁBms
        unsigned long	_tmModeBase;	// ���̃��[�h���n�܂������ԁBms
        unsigned long	_tmPauseBase;	// �|�[�Y���̃x�[�X���ԁBms
        unsigned long	_tmPauseStep;	// �|�[�Y���̐ώZ���ԁBms ���쒆�A���̒l�� _tmMode �ɗp����
        unsigned long	_tmOldFrame;	// �O�t���[���̎��ԁBms

        // CallPerFrame / CallOfCount�p
        int		_callPerFrame, _callPerFrame_cnt;
        int		_callOfCount;
        std::unique_ptr<ObjectServer> _objectServer;
        std::unique_ptr<UICanvasServer> _uiCanvasServer;
        std::unique_ptr<BlurRenderer> _blurRenderer;
        bool _blurActivate;
    };
}
