#include <windows.h>
#include <process.h>

#pragma once
class ThreadBase
{
public:
	ThreadBase();
	virtual ~ThreadBase();

	/// �X���b�h�̊J�n 
	virtual	bool	ThreadStart();

	/// �X���b�h�̏�Ԋm�F 
	virtual	bool	IsThreadExec();

protected:
	/// �X���b�h���s�v���Z�X 
	virtual		bool	ThreadProc() = 0;

private:
	/// �X���b�h����p
	bool	_bExec;
	HANDLE	_hThread;
	/// ������֐� 
	static  unsigned __stdcall	ThreadProcBase(void* lpx);
};

