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
	ThreadBase* cls = (ThreadBase*)lpx;		// _beginthreadex()�œn���ꂽthis�|�C���^���N���X�|�C���^�ɃL���X�g
	cls->ThreadProc();		// �X���b�h�̓��� 
	cls->_bExec = false;	// �X���b�h�̏I��
	return 0;
}