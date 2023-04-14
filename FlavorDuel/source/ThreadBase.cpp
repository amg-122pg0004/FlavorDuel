#include "ThreadBase.h"
ThreadBase::ThreadBase() {
	_bExec = false;
	_hThread = NULL;
}

ThreadBase::~ThreadBase() {
	if (_hThread) {
		CloseHandle(_hThread);
		_hThread = NULL;
	}
}

bool	ThreadBase::ThreadStart() {
	unsigned int thID;
	_bExec = true;
	_hThread = (HANDLE)_beginthreadex(NULL, 0, ThreadBase::ThreadProcBase, this, 0, &thID);
	return	true;
}

bool	ThreadBase::IsThreadExec() {
	return	_bExec;
}

unsigned __stdcall ThreadBase::ThreadProcBase(void* lpx) {
	ThreadBase* cls = (ThreadBase*)lpx;		// _beginthreadex()で渡されたthisポインタをクラスポインタにキャスト
	cls->ThreadProc();		// スレッドの動作 
	cls->_bExec = false;	// スレッドの終了
	return 0;
}