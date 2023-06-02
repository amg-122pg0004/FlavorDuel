/*****************************************************************//**
 * \file   RoomState.h
 * \brief  サーバー側の待機状態を示す列挙子　WaitPlayの時のみ操作を受け付ける
 * ゲームの進行はこちらではなくSequenceで管理
 * 
 * \author 土居将太郎
 * \date   May 2023
 *********************************************************************/
#pragma once
namespace Flavor {
	enum class RoomState {
		WaitPlay,//クライアントからのカード選択を受け付ける
		WaitAnalyze,//ChatGPTの処理待ち
		FinishGame
	};
}