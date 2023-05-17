/*****************************************************************//**
 * \file   SequenceMessages.h
 * \brief  ゲーム中の現在の進行状況の列挙型
 *         IObserverSequence,ISequenceSubjestで送受信する
 * 
 * \author 土居将太郎
 * \date   May 2023
 *********************************************************************/
#pragma once
enum SequenceMessages{
	GameStart,
	TurnStart,
	CardSelect,
	Battle,
	TurnEnd
};