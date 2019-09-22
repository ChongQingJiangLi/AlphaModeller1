#pragma once
#include "CVertex.h"
#include "CLoopEdgeLink.h"
#include "CCurve.h"
namespace AlphaModeller {

	class CEdge {

		// data
	public:
		CLoopEdgeLink *_rightLinkPtr = nullptr;//pointer to a loop-edge link on the right of the edge
		CLoopEdgeLink *_leftLinkPtr = nullptr;//pointer to a loop-edge link on the left of the edge
		AlphaModeller::CVertex *_startVertexPtr = nullptr;//pointer to the start vertex of the edge
		AlphaModeller::CVertex *_endVertexPtr = nullptr;//pointer to the end vertex of the edge
		CEdge *_nextEdgePtr = nullptr;//pointer to the next edge in the "all edges in body chain"
		CEdge *_preEdgePtr = nullptr;//pointer to the previous edge in the "all edges in body chain"
		CCurve *_curvePtr = nullptr;//pointer to the geometric definition of the edge
		CEdge *_friendEdgePtr = nullptr;//for associating non-manifold edges

		//pointer to an edge or supplementary geometry entity
		//owner pointer
		//pointer to a list of information elements associated with the edge
		//pointer to the head of a chain of group links to the groups containing the edge
		CSpace *_spaceBoxPtr = nullptr;
		unsigned int _markerBits = 0;
		unsigned int _edgeID;
		//pointer to the name of the edge

		//operation
	public:
		CEdge(CVertex* startVertexPtr, CVertex* endVertexPtr) :
			_startVertexPtr(startVertexPtr), _endVertexPtr(endVertexPtr), _edgeID(_curID++) {};

		CEdge(CVertex* startVertexPtr, CVertex* endVertexPtr, CCurve *curvePtr) :
			_startVertexPtr(startVertexPtr), _endVertexPtr(endVertexPtr), _curvePtr(curvePtr), _edgeID(_curID++) {};
		/*CEdge(CVertex* startVertexPtr, CLoop* loopPtr) :
			_startVertexPtr(startVertexPtr), _edgeID(_curID++) {};*/
		
		~CEdge();
	private:
		static unsigned long long int _curID;
	};
	void connect_edge_to_vertex(CEdge* edgePtr);
	CLoopEdgeLink* find_other_loop_edge_link_of_edge(CLoopEdgeLink* loopEdgeLink)
	{
		return (loopEdgeLink == loopEdgeLink->_edgePtr->_rightLinkPtr ?
			loopEdgeLink->_edgePtr->_leftLinkPtr :
			loopEdgeLink->_edgePtr->_rightLinkPtr);
	}
	CEdge* create_edge(AlphaModeller::CVertex* startVertexPtr, AlphaModeller::CVertex* endVertexPtr)
	{
		CEdge* _edgePtr =  new CEdge(startVertexPtr, endVertexPtr);
		startVertexPtr->_edgePtrVector.push_back(_edgePtr);
		endVertexPtr->_edgePtrVector.push_back(_edgePtr);
		return _edgePtr;
	}
	AlphaModeller::CEdge* create_edge(AlphaModeller::CVertex* startVertexPtr, AlphaModeller::CVertex* endVertexPtr,CCurve* curPtr)
	{
		CEdge* _edgePtr = new CEdge(startVertexPtr, endVertexPtr, curPtr);
		startVertexPtr->_edgePtrVector.push_back(_edgePtr);
		endVertexPtr->_edgePtrVector.push_back(_edgePtr);
		return _edgePtr;
	}
	//change the vertex of a edge without deleting the vertex or edge
	void change_edge_vertex(CEdge* edgePtr, CVertex* preVertexPtr, CVertex* newVertexPtr) {
		//change the vertex pointer
		if (edgePtr->_startVertexPtr == preVertexPtr) {
			edgePtr->_startVertexPtr = newVertexPtr;
		}
		else if(edgePtr->_endVertexPtr==preVertexPtr){
			edgePtr->_endVertexPtr = newVertexPtr;
		}
		else {
		//shouldn't happen
		}

		//change the edge vector of the vertex
		CEdgePtrVector::iterator _edgePtrIterator;
		_edgePtrIterator = std::find(preVertexPtr->_edgePtrVector.begin(),
									 preVertexPtr->_edgePtrVector.end(),
									 edgePtr);
		preVertexPtr->_edgePtrVector.erase(_edgePtrIterator);

		newVertexPtr->_edgePtrVector.push_back(edgePtr);

		//change the edge pointer of the vertex
		newVertexPtr->_edgePtr = edgePtr;

		if (preVertexPtr->_edgePtrVector.size() == 0) {
			preVertexPtr->_edgePtr = nullptr;
		}
		else {
			preVertexPtr->_edgePtr = preVertexPtr->_edgePtrVector.back();
		}
	}
}