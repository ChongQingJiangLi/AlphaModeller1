#include "pch.h"
#include "CFace.h"
#include"CLoop.h"
#include<algorithm>
#include<vector>



AlphaModeller::CFaceGroup::CFaceGroup()
{
}

AlphaModeller::CFaceGroup::~CFaceGroup()
{
}

AlphaModeller::CFace::~CFace()
{
	/*while (_loopPtr) {
		CLoop* temp = _loopPtr;
		_loopPtr = _loopPtr->_nextLoopPtr;
		delete temp;
	}*/

	if (_faceID == _curID - 1) _curID--; 
}

void AlphaModeller::CFace::delete_loop(CLoop * loopPtr)
{
	if (_loopPtr == loopPtr) _loopPtr = loopPtr->_nextLoopPtr;
	if (loopPtr->_preLoopPtr) loopPtr->_preLoopPtr->_nextLoopPtr = loopPtr->_nextLoopPtr;
	if (loopPtr->_nextLoopPtr) loopPtr->_nextLoopPtr->_preLoopPtr = loopPtr->_preLoopPtr;
	delete loopPtr;
}

AlphaModeller::CLoop * AlphaModeller::CFace::new_loop(CFace* facePtr)
{
	CLoop* _loopPtr = new CLoop(this);
	return _loopPtr;
}
AlphaModeller::CLoop * AlphaModeller::CFace::new_loop()
{
	CLoop* _loopPtr = new CLoop(this);
	return _loopPtr;
}
void AlphaModeller::CFace::connect_loop(CLoop * loopPtr)
{
	if (loopPtr) {
		_loopPtrVector.push_back(loopPtr);
	}
}

void AlphaModeller::CFace::disconnect_loop(CLoop * loopPtr)
{
	decltype(_loopPtrVector)::iterator _loopIterator;
	_loopIterator = std::find(_loopPtrVector.begin(),_loopPtrVector.end(),loopPtr);
	if (_loopIterator != _loopPtrVector.end()) {
		(*_loopIterator)->_facePtr = nullptr;
		_loopPtrVector.erase(_loopIterator);
	}
}

