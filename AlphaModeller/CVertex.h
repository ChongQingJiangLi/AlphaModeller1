#pragma once
#include "CEdge.h"
#include "CLoop.h"
#include "CPoint.h"
#include<vector>
//#include"CObject.h"


namespace AlphaModeller {
	
	class CVertex {

	// data
	public:
		CEdge* _edgePtr = nullptr;//pointer to one edge at the vertex
		CLoop* _loopPtr = nullptr;//pointer to the loop owning the vertex if there are no attached edges
		CPoint* _positionPtr = nullptr;//pointer to the geometry of the vertex
		CVertex* _nextVertexPtr = nullptr;
		CVertex* _preVertexPtr = nullptr;
		CVertex* _friendPtr = nullptr;//for associating non-maniford vertices
		unsigned int _markerBits = 0;//marker bits for modelling operations
		unsigned int _vertexID;//vertex ID
		CEdgePtrVector _edgePtrVector;
		//information list pointer
		//pointer to the head of a chain of group links to the groups containing the vertex

	//operation
	public:
		//friend class CVolumeObject;
		CVertex(CPoint* positionPtr) : _vertexID(_curID++) , _positionPtr(positionPtr){};
		CVertex(CPoint position) : _vertexID(_curID++), _positionPtr(&position) {};
		CVertex() : _vertexID(_curID++) {};
		~CVertex() { if (_vertexID == _curID - 1) _curID--; };
	private:
		static unsigned long long int _curID;
	};



}








