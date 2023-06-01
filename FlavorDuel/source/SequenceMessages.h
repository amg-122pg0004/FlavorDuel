/*****************************************************************//**
 * \file   InGameSequence.h
 * \brief  �Q�[�����̌��݂̐i�s�󋵂̗񋓌^
 *         IObserverSequence,ISequenceSubjest�ő���M����
 *
 * \author �y�������Y
 * \date   May 2023
 *********************************************************************/
#pragma once
enum InGameSequence {
	BeginGame,
	StartTurn,
	WaitPlay,
	WaitAnalyze,
	Judge,
	EndTurn,
	FinishGame,
};