#pragma once
#include "CEdge.h"
#include "CVertex.h"
namespace AlphaModeller {

	class CLoopEdgeLink {

		// data
	public:
		CEdge* _edgePtr = nullptr;//pointer to the edge owning the link
		CLoop* _loopPtr = nullptr;//pointer to the loop owning the link
		//CVertex *_vertexPtr = nullptr;
		CLoopEdgeLink *_nextLoopEdgeLinkPtr = nullptr;
		CLoopEdgeLink *_preLoopEdgeLinkPtr = nullptr;
		
	//operation	
	public:
		CLoopEdgeLink(CEdge* edgePtr) :_edgePtr(edgePtr) {};
		CLoopEdgeLink(CLoop* loopPtr) :_loopPtr(loopPtr) { 
			if (!loopPtr) {
				loopPtr->_loopEdgeLinkPtr = this;
			} 
		};
		CLoopEdgeLink(CLoopEdgeLink* nextLoopEdgeLinkPtr) :
			_loopPtr(nextLoopEdgeLinkPtr->_loopPtr), _nextLoopEdgeLinkPtr(nextLoopEdgeLinkPtr), _preLoopEdgeLinkPtr(nextLoopEdgeLinkPtr->_preLoopEdgeLinkPtr) {
			nextLoopEdgeLinkPtr->_preLoopEdgeLinkPtr->_nextLoopEdgeLinkPtr = this;
			nextLoopEdgeLinkPtr->_preLoopEdgeLinkPtr = this;
		};
		~CLoopEdgeLink();
		CLoopEdgeLink* find_opposite_loop_edge_link();
	};
	

}