/*****************************************************************//**
 * \file   RoomState.h
 * \brief  �T�[�o�[���̑ҋ@��Ԃ������񋓎q�@WaitPlay�̎��̂ݑ�����󂯕t����
 * �Q�[���̐i�s�͂�����ł͂Ȃ�Sequence�ŊǗ�
 * 
 * \author �y�������Y
 * \date   May 2023
 *********************************************************************/
#pragma once
namespace Flavor {
	enum class RoomState {
		WaitPlay,//�N���C�A���g����̃J�[�h�I�����󂯕t����
		WaitAnalyze,//ChatGPT�̏����҂�
		FinishGame
	};
}