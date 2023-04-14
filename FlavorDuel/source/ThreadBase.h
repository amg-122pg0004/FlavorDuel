#include <windows.h>
#include <process.h>

#pragma once
class ThreadBase
{
public:
	ThreadBase();
	virtual ~ThreadBase();

	/// スレッドの開始 
	virtual	bool	ThreadStart();

	/// スレッドの状態確認 
	virtual	bool	IsThreadExec();

protected:
	/// スレッド実行プロセス 
	virtual		bool	ThreadProc() = 0;

private:
	/// スレッド動作用
	bool	_bExec;
	HANDLE	_hThread;
	/// 動作基底関数 
	static  unsigned __stdcall	ThreadProcBase(void* lpx);
};

