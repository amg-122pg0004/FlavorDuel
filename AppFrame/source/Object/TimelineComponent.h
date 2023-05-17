/*****************************************************************//**
 * \file   TimelineComponent.h
 * \brief  �L�[�t���[���ƕ�ԕ��@��ݒ肵�āA�^�C�����C�����쐬�E�Z�b�g���܂��BGetValue�Œl��Ԃ��܂��B
 * \brief�@_visble��true�ɂ���ƃf�o�b�O���[�h�ŃO���t�̋Ȑ����m�F�ł��܂�
 *
 * \author �y�������Y
 * \date   February 2023
 *********************************************************************/
#pragma once
#include <vector>
#include "ComponentBase.h"
#include "Utility/Easing.h"
namespace AppFrame {
	class TimelineComponent : public ComponentBase
	{
	public:
		struct KeyFrame
		{
			float time;
			float value;
			EasingType type;
		};

		enum class PlayType {
			OnceNormal,//����1��Đ�
			OnceReverse,//�t��1��Đ�
			OnceNormalAndReverce,//�������t����1��Đ�
			LoopNormal,//�������[�v�Đ�
			LoopReverse,//�t�����[�v�Đ�
			LoopNormalAndReverce,//�������t�������[�v�Đ�
		};

		using TimeLine = std::vector<KeyFrame>;

		TimelineComponent();
		bool Init()override;
		void Update(InputManager& input)override;
		void Debug()override;
		//�l���擾(�R���|�[�l���g���ɂ���^�C�}�[���Ԃ��g�p)
		std::vector<float> GetValue();
		//�w�肵�����Ԃ̒l���擾
		std::vector<float> GetValueParticularTime(float time);
		//�^�C�����C����ݒ�
		void SetTimeLine(TimeLine timeline);
		void SetTimeLine(std::vector<TimeLine> timeline);
		PlayType GetPlayType() { return _playType; }
		//�Đ��^�C�v��ݒ�
		void SetPlayType(PlayType type);
		//�Đ���~�A�ĊJ��ݒ�
		void SetStop(bool flag) { _stop = flag; }
		bool GetStop() { return _stop; }
		//�^�C�}�[���ŏ��ɖ߂�
		void ResetTime();

		void SetDebugVisible(bool flag) { _debugVisible = flag; }
	private:
		std::vector<TimeLine> _timeLines;//�L�[�͎��ԁA�l��first�ݒ�l,second��ԕ��@
		float GetMax();//�ő�̐ݒ�l
		float GetMin();//�ŏ��̐ݒ�l
		void DrawDebugImage();//�f�o�b�O�p�̃O���t�̋Ȑ���ݒ�

		PlayType _playType;
		bool _reverse;
		bool _loop;
		bool _bothWays;
		bool _stop;//�X�V���s����
		float _time;//���݂̎���
		float _timeMax;//�S�̂̎���

		int _debugImage;
		bool _debugVisible;
	};
}
