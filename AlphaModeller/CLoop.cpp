#include "CLoop.h"

AlphaModeller::CLoop::CLoop(CFace* facePtr) : _facePtr(facePtr)
{
	if (facePtr != nullptr) {
		facePtr->_loopPtrVector.push_back(this);
	}
}

AlphaModeller::CLoop::~CLoop()
{
}

void AlphaModeller::CLoop::append_to_loop_list()
{
	if (_facePtr->_loopPtr) {
		CLoop* _tempLoopPtr = _facePtr->_loopPtr;
		for (; _tempLoopPtr->_nextLoopPtr; _tempLoopPtr= _tempLoopPtr->_nextLoopPtr);//空语句
		_tempLoopPtr->_nextLoopPtr =const_cast<decltype(_tempLoopPtr)> (this);
		_preLoopPtr = _tempLoopPtr;
	
	}
	else {
		_facePtr->_loopPtr = this;
	}
}

unsigned int AlphaModeller::CLoop::total_vertex() const
{
	unsigned int totalNum = 0;
	CLoopEdgeLink* curLink = _loopEdgeLinkPtr;
	do
	{
		totalNum++;
	} while ((curLink= curLink->_nextLoopEdgeLinkPtr)!=_loopEdgeLinkPtr);
	return totalNum;
}

void AlphaModeller::CLoop::connect_loop_edge_link(CLoopEdgeLink * loopEdgeLink)
{
	loopEdgeLink->_loopPtr = this;
	if (_loopEdgeLinkPtr == nullptr) {
		loopEdgeLink->_nextLoopEdgeLinkPtr = loopEdgeLink;
		loopEdgeLink->_preLoopEdgeLinkPtr = loopEdgeLink;
		_loopEdgeLinkPtr = loopEdgeLink;
	}else {
		loopEdgeLink->_nextLoopEdgeLinkPtr = _loopEdgeLinkPtr;
		loopEdgeLink->_preLoopEdgeLinkPtr = _loopEdgeLinkPtr->_preLoopEdgeLinkPtr;
		loopEdgeLink->_preLoopEdgeLinkPtr->_nextLoopEdgeLinkPtr = loopEdgeLink;
		loopEdgeLink->_nextLoopEdgeLinkPtr->_preLoopEdgeLinkPtr = loopEdgeLink;
	}
}

void AlphaModeller::CLoop::disconnect_loop_edge_link(CLoopEdgeLink * loopEdgeLink)
{
	if (!loopEdgeLink->_nextLoopEdgeLinkPtr || !loopEdgeLink->_preLoopEdgeLinkPtr) {
		//something is wrong
	}
	//first loop edge link
	if (_loopEdgeLinkPtr == loopEdgeLink) {
		if (_loopEdgeLinkPtr->_nextLoopEdgeLinkPtr == _loopEdgeLinkPtr) {
			_loopEdgeLinkPtr = nullptr;
		}
		else {
			_loopEdgeLinkPtr = loopEdgeLink->_nextLoopEdgeLinkPtr;
		}
	}
	if (loopEdgeLink->_nextLoopEdgeLinkPtr) {
		loopEdgeLink->_nextLoopEdgeLinkPtr->_preLoopEdgeLinkPtr = loopEdgeLink->_preLoopEdgeLinkPtr;
	}
	if (loopEdgeLink->_preLoopEdgeLinkPtr) {
		loopEdgeLink->_preLoopEdgeLinkPtr->_nextLoopEdgeLinkPtr = loopEdgeLink->_nextLoopEdgeLinkPtr;
	}
	loopEdgeLink->_loopPtr = nullptr;
	loopEdgeLink->_nextLoopEdgeLinkPtr = nullptr;
	loopEdgeLink->_preLoopEdgeLinkPtr = nullptr;
}	

AlphaModeller::CLoopEdgeLink * AlphaModeller::CLoop::create_loop_edge_link(CVertex * startVertexPtr, CVertex * endVertexPtr)
{
	//上一个半边的尾必须是新建半边的头
	if (_loopEdgeLinkPtr && (_loopEdgeLinkPtr->_preLoopEdgeLinkPtr)->_edgePtr->_endVertexPtr != startVertexPtr) {
		//inform the world something is wrong;
		return nullptr;
	}
	// create a loop edge link that needs to be connected in the loop
	CLoopEdgeLink* _loopEdgeLinkPtr = create_loop_edge_link_without_loop(startVertexPtr,endVertexPtr);

	// connect the loop edge link in the loop
	connect_loop_edge_link(_loopEdgeLinkPtr);

	// add the edge pointer to the start and end vertex
	_loopEdgeLinkPtr->_edgePtr->_startVertexPtr->_edgePtrVector.push_back(_loopEdgeLinkPtr->_edgePtr);
	_loopEdgeLinkPtr->_edgePtr->_endVertexPtr->_edgePtrVector.push_back(_loopEdgeLinkPtr->_edgePtr);
	return _loopEdgeLinkPtr;
}

AlphaModeller::CLoopEdgeLink * AlphaModeller::CLoop::create_loop_edge_link_without_loop(CVertex * startVertexPtr, CVertex * endVertexPtr)
{
	CLoopEdgeLink* _loopEdgeLinkPtr = nullptr;
	CEdge* _edgePtr = find_edge(startVertexPtr,endVertexPtr);
	//there is no edge containing both two loop edge links between two vertexes
	if (_edgePtr == nullptr) {
		_edgePtr = create_edge(startVertexPtr, endVertexPtr);
		// return the right loop edge link poiter
		_loopEdgeLinkPtr = _edgePtr->_rightLinkPtr;
	}
	else {
		if (_edgePtr->_rightLinkPtr!=nullptr) {
			_loopEdgeLinkPtr = _edgePtr->_rightLinkPtr;
		}
		else if (_edgePtr->_leftLinkPtr!=nullptr) {
			_loopEdgeLinkPtr = _edgePtr->_leftLinkPtr;
		}
		else {
			//shouldn't happen
			return nullptr;
		}
		//if the loop edge link already used in a loop, create a duplicate edge
		if (_loopEdgeLinkPtr->_loopPtr) {
			_edgePtr = create_edge(startVertexPtr, endVertexPtr);
			// return the right loop edge link poiter
			_loopEdgeLinkPtr = _edgePtr->_rightLinkPtr;
		}
	}

	return _loopEdgeLinkPtr;
}
AlphaModeller::CEdge * AlphaModeller::CLoop::create_edge_without_loop(CVertex * startVertexPtr, CVertex * endVertexPtr,CCurve* curPtr)
{
	CEdge* _edgePtr = find_edge(startVertexPtr, endVertexPtr);
	//there is no edge containing both two loop edge links between two vertexes
	if (_edgePtr == nullptr) {
		_edgePtr = create_edge(startVertexPtr, endVertexPtr,curPtr);
	}
	else {
		
		//if the loop edge link already used in a loop, create a duplicate edge
		if (_edgePtr->_rightLinkPtr || _edgePtr->_leftLinkPtr) {
			_edgePtr = create_edge(startVertexPtr, endVertexPtr);
		}
	}

	return _edgePtr;
}
AlphaModeller::CEdge * AlphaModeller::CLoop::create_edge_with_loop(CVertex * startVertexPtr, CVertex * endVertexPtr, CCurve * curPtr)
{
	//上一个半边的尾必须是新建半边的头
	if (_loopEdgeLinkPtr && (_loopEdgeLinkPtr->_preLoopEdgeLinkPtr)->_edgePtr->_endVertexPtr != startVertexPtr) {
		//inform the world something is wrong;
		return nullptr;
	}
	// create a loop edge link that needs to be connected in the loop
	CEdge* _edgePtr = create_edge_without_loop(startVertexPtr, endVertexPtr,curPtr);

	// connect the loop edge link in the loop
	connect_loop_edge_link(_edgePtr->_rightLinkPtr);
	_loopEdgeLinkPtr->find_opposite_loop_edge_link()->_loopPtr->connect_loop_edge_link(_edgePtr->_leftLinkPtr);
	// add the edge pointer to the start and end vertex
	connect_edge_to_vertex(_edgePtr);
	return _edgePtr;
}
/*
AlphaModeller::CEdge * AlphaModeller::find_edge(AlphaModeller::CVertex * startVertexPtr, AlphaModeller::CVertex * endVertexPtr)
{
	AlphaModeller::CEdgePtrVector _edgePtrVector;
	_edgePtrVector = startVertexPtr->_edgePtrVector;
	for (auto &_edgePtrIterator : _edgePtrVector) {
		if (_edgePtrIterator->_endVertexPtr == endVertexPtr) {
			return _edgePtrIterator;
		}
	}
	_edgePtrVector = endVertexPtr->_edgePtrVector;
	for (auto &_edgePtrIterator : _edgePtrVector) {
		if (_edgePtrIterator->_startVertexPtr == startVertexPtr) {
			return _edgePtrIterator;
		}
	}
	return nullptr;
}
*/

