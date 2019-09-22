#include "CEdge.h"
#include<vector>
#include<algorithm>
AlphaModeller::CEdge::CEdge(CVertex * startVertexPtr, CVertex * endVertexPtr):
	_startVertexPtr(startVertexPtr), _endVertexPtr(endVertexPtr)
{
	_rightLinkPtr = new CLoopEdgeLink(this);
	_leftLinkPtr = new CLoopEdgeLink(this);
	
	//_rightLinkPtr->_edgePtr = this;
	//_leftLinkPtr->_edgePtr = this;
}

AlphaModeller::CEdge::CEdge(CVertex * startVertexPtr, CVertex * endVertexPtr, CCurve * curvePtr):
	_startVertexPtr(startVertexPtr), _endVertexPtr(endVertexPtr), _curvePtr(curvePtr)
{
	_rightLinkPtr = new CLoopEdgeLink(this);
	_leftLinkPtr = new CLoopEdgeLink(this);
	
	//_rightLinkPtr->_edgePtr = this;
	//_leftLinkPtr->_edgePtr = this;
}
/*
AlphaModeller::CEdge::CEdge(CVertex* startVertexPtr, CLoop* loopPtr) :
	_startVertexPtr(startVertexPtr), _edgeID(_curID++)
{
	_rightLinkPtr = new CLoopEdgeLink(this);
}
*/

AlphaModeller::CEdge::~CEdge()
{
	if (_rightLinkPtr->_loopPtr || _leftLinkPtr->_loopPtr) {
	//warn the wolrd that something is wrong

	}
	else {
		delete _leftLinkPtr, _rightLinkPtr;
	
	}
	CEdgePtrVector::iterator _edgePtrVectorIterator;
	_edgePtrVectorIterator = std::find(this->_endVertexPtr->_edgePtrVector.begin(),
									   this->_endVertexPtr->_edgePtrVector.end(),this);
	this->_endVertexPtr->_edgePtrVector.erase(_edgePtrVectorIterator);

	_edgePtrVectorIterator = std::find(this->_startVertexPtr->_edgePtrVector.begin(),
									   this->_startVertexPtr->_edgePtrVector.end(), this);
	this->_startVertexPtr->_edgePtrVector.erase(_edgePtrVectorIterator);


	if (_edgeID == _curID - 1) _curID--;
}

void AlphaModeller::connect_edge_to_vertex(CEdge * edgePtr)
{
	edgePtr->_startVertexPtr->_edgePtrVector.push_back(edgePtr);
	edgePtr->_endVertexPtr->_edgePtrVector.push_back(edgePtr);
}
