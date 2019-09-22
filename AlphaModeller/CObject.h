#pragma once
#include "CEdge.h"
#include "CVertex.h"
#include "CShell.h"
#include "CInstance.h"
#include <vector>

namespace AlphaModeller {

	class CObject {

		// data
	public:
		//pointer to a list of information elements associated with the edge
		//pointer to the head of a chain of group links to the groups containing the object
		CSpace *spacePtr=nullptr;
		unsigned int _markerBits = 0;
		unsigned int _refNum = 0;//the number of referenced times
		unsigned int _externRefNum = 0;//the number of externally referenced times
		unsigned int _objectID = 0;
		//pointer to the name of the object

		//operation
	public:
		CObject();
		~CObject();
	};

	class CWireframeObject :public CObject {

	public:
		CEdge *_edgePtr = nullptr;
		AlphaModeller::CVertex *_vertexPtr = nullptr;

	public:
		CWireframeObject();
		~CWireframeObject();

	};

	class CSheetObject :public CObject {

	public:
		std::vector<AlphaModeller::CEdge> _edgeVector;
		std::vector<AlphaModeller::CVertex> _vertexVector;
		std::vector<AlphaModeller::CShell> _shellVector;
		
	public:
		CSheetObject();
		~CSheetObject();

	};

	using CEdgeVector = std::vector<AlphaModeller::CEdge>;
	using CVertexVector = std::vector<AlphaModeller::CVertex>;
	using CShellVector = std::vector<AlphaModeller::CShell>;
	using CLoopEdgeLinkVector = std::vector<AlphaModeller::CLoopEdgeLink>;
	using CLoopVector = std::vector<AlphaModeller::CLoop>;
	using CPointVector = std::vector<AlphaModeller::CPoint>;
	using CCurveVector = std::vector<AlphaModeller::CCurve>;
	using CSurfaceVector = std::vector<AlphaModeller::CSurface>;

	using CEdgePtrVector = std::vector<AlphaModeller::CEdge*>;
	using CVertexPtrVector = std::vector<AlphaModeller::CVertex*>;
	using CShellPtrVector = std::vector<AlphaModeller::CShell*>;
	using CLoopEdgeLinkPtrVector = std::vector<AlphaModeller::CLoopEdgeLink*>;
	using CLoopPtrVector = std::vector<AlphaModeller::CLoop*>;
	using CPointPtrVector = std::vector<AlphaModeller::CPoint*>;
	using CCurvePtrVector = std::vector<AlphaModeller::CCurve*>;
	using CSurfacePtrVector = std::vector<AlphaModeller::CSurface*>;
	using CVertex = AlphaModeller::CVertex;
	

	class CVolumeObject :public CObject {
		
	public:
		/*CEdge *_edgePtr = nullptr;
		CVertex *_vertexPtr = nullptr;
		CShell *_shellPtr = nullptr;*/
		
		static CVolumeObject* _staticVolumeObjectPtr;
		CVolumeObject* _preVolumeObject = nullptr;
		CVolumeObject* _nextVolumeObject = nullptr;
		//pointer to the head of a chain of feasure records

		//long long int _vertexIDNumMax = 0;
	private:
		static unsigned long long int _curID;
	public:
		CVolumeObject() {_objectID = _curID++; };
		~CVolumeObject() { if (_objectID == _curID - 1) { _curID--; } };
		/********************* topology geometry operation**************************/
		CShell* new_shell(CVolumeObject* objectPtr);
		//CFace* new_face();
		//CLoop* new_loop();
		void connect_shell(CShell* shellPtr);
		/******************** traversal operation **********************************/
		/*topological set tranversal*/
		//edges in vertex
		void find_edges_in_vertex(AlphaModeller::CVertex * targetVertexPtr, CEdgeVector &resultEdgeVector, const CEdgeVector * edgeVector);
		

		/******************** euler operation *****************************/
		static CVolumeObject* mvfs(CPoint *pointPtr);
		 void mev(AlphaModeller::CVertex *vertex, CPoint *position, CCurve *curPtr);//spur an edge and vertex
		 void mev(AlphaModeller::CVertex *startVertexPtr, CEdge *edgePtr, CPoint *position);//split an edge(inserting a vertex in an edge)
		 //void mev(AlphaModeller::CVertex *splitVertexPtr, CEdge *preEdgePtr,CEdge *nextEdgePtr,CPoint *position, CCurve *curPtr);//split an vertex(inserting an edge between two edges)
		 void mef(CShell*shellPtr,
				  AlphaModeller::CVertex * startVertexPtr,
				  AlphaModeller::CVertex * endVertexPtr,
				  CEdge* startEdgePtr,
				  CEdge* endEdgePtr,
				  CCurve* curPtr,
				  CSurface *surfacePtr);
		 //void mef(CLoop *outLoop, AlphaModeller::CVertex *vertex1, AlphaModeller::CVertex *vertex2, AlphaModeller::CVertex *vertex3, AlphaModeller::CVertex *vertex4);
		 void kemr(CLoop *outLoop, CEdge *edge, AlphaModeller::CVertex *vertexOnOutLoop);
		 void kfmhr(CFace *outFace, CFace *innerFace);

	};

	AlphaModeller::CVertex* add_vertex(CVolumeObject* objectPtr,CPoint &point);
	class CObjectGroup {

		//data
	public:
		CInstance *_firstInstancePtr = nullptr;
		CSpace *_spacePtr = nullptr;
		//pointer to a list of information elements associated with the edge
		//pointer to the head of a chain of group links to the groups containing the object group
		//pointer to the name of the group of objects
		unsigned int _markerBits = 0;
		unsigned int _objectGroupID = 0;
		unsigned int _refNum = 0;
		unsigned int _extRefNum = 0;

		//operation
	public:
		CObjectGroup();
		~CObjectGroup();

	};

}
