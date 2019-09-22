#pragma once
#include "CFace.h"
#include "CEdge.h"
#include "CVertex.h"

namespace AlphaModeller {

	class CLoop {

		// data
	public:
		CFace *_facePtr = nullptr;
		CLoopEdgeLink *_loopEdgeLinkPtr = nullptr;
		CVertex *_vertexPtr = nullptr;
		CLoop *_nextLoopPtr = nullptr;
		CLoop *_preLoopPtr = nullptr;
		unsigned int _loopID;
		bool _holeLoop=false;
		unsigned int _markerBits = 0;
		//information list pointer
		//pointer to the head of a chain of group links to the groups containing the loop


		//operation
	public:
		CLoop(CFace* facePtr) :_facePtr(facePtr) {};
		~CLoop();
		void append_to_loop_list();
		void set_loop_head(CLoopEdgeLink* headLoopEdgeLink) { _loopEdgeLinkPtr = headLoopEdgeLink; };
		unsigned int total_vertex() const;
		void connect_loop_edge_link(CLoopEdgeLink* loopEdgeLink);
		void disconnect_loop_edge_link(CLoopEdgeLink* loopEdgeLink);
		CLoopEdgeLink* create_loop_edge_link(AlphaModeller::CVertex* startVertexPtr, AlphaModeller::CVertex* endVertexPtr);
		CLoopEdgeLink* create_loop_edge_link_without_loop(AlphaModeller::CVertex* startVertexPtr, CVertex* endVertexPtr);
		//CEdge* find_edge(CVertex* startVertexPtr,CVertex* endVertexPtr);
		CEdge* create_edge_without_loop(CVertex * startVertexPtr, CVertex * endVertexPtr, CCurve* curPtr);
		CEdge* create_edge_with_loop(CVertex * startVertexPtr, CVertex * endVertexPtr, CCurve* curPtr);
	};

	CEdge * find_edge(AlphaModeller::CVertex * startVertexPtr, AlphaModeller::CVertex * endVertexPtr) 
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
	
	void insert_loop_edge_link(CLoop* loopPtr,CLoopEdgeLink* startLoopEdgeLinkPtr,CLoopEdgeLink* insertLoopEdgeLinkPtr)
	{
		loopPtr->_loopEdgeLinkPtr = startLoopEdgeLinkPtr;
		loopPtr->connect_loop_edge_link(insertLoopEdgeLinkPtr);
	}
}

