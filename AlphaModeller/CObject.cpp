#include "CObject.h"
#include"CVertex.h"
#include "CLoop.h"
using namespace AlphaModeller;
using CVertex = AlphaModeller::CVertex;
namespace AlphaModeller {
	AlphaModeller::CObject::CObject()
	{

	}

	AlphaModeller::CObject::~CObject()
	{

	}

	AlphaModeller::CWireframeObject::CWireframeObject()
	{

	}

	AlphaModeller::CWireframeObject::~CWireframeObject()
	{

	}

	AlphaModeller::CSheetObject::CSheetObject()
	{

	}

	AlphaModeller::CSheetObject::~CSheetObject()
	{

	}

	AlphaModeller::CVolumeObject::CVolumeObject()
	{

	}

	AlphaModeller::CVolumeObject::~CVolumeObject()
	{

	}



	AlphaModeller::CShell * AlphaModeller::CVolumeObject::new_shell(CVolumeObject * objectPtr)
	{
		CShell *_shellPtr = new CShell(objectPtr);
		return _shellPtr;
	}

	void AlphaModeller::CVolumeObject::connect_shell(CShell * shellPtr)
	{
		shellPtr->_ownerObjectPtr = this;
		this->_shellVector.push_back(*shellPtr);
	}



	void AlphaModeller::CVolumeObject::find_edges_in_vertex(CVertex * targetVertexPtr, CEdgeVector &resultEdgeVector, const CEdgeVector * edgeVector)
	{
		//CEdgeVector _resultEdgeVector;
		for (auto &_edge : (*edgeVector)) {
			if (_edge._startVertexPtr == targetVertexPtr || _edge._endVertexPtr == targetVertexPtr) {
				resultEdgeVector.push_back(_edge);
			}
		}
	}

	AlphaModeller::CVolumeObject * AlphaModeller::CVolumeObject::mvfs(CPoint *pointPtr)
	{
		CVolumeObject *s = new CVolumeObject();
		CShell* _shellPtr=s->new_shell(s);
		CFace* _facePtr = _shellPtr->new_face(_shellPtr);
		CLoop* _loopPtr=_facePtr->new_loop(_facePtr);
		CVertex* _vertexPtr=add_vertex(s, *pointPtr);
		return s;
	}

	void AlphaModeller::CVolumeObject::mev(AlphaModeller::CVertex * vertexPtr, CPoint * positionPtr,CCurve *curPtr)
	{
		AlphaModeller::CVertex *_newVertexPtr = add_vertex(this,*positionPtr);
		CEdge *_newEdgePtr = new CEdge(vertexPtr,_newVertexPtr,curPtr);
		//创建了新edge后，需要把该edge对应的loop edge link与vertex相连接的edge对应的loop edge link创建关系
		if (vertexPtr->_edgePtrVector.size() == 0) {
			//vertex has no attached edges except the new edge
			insert_loop_edge_link(vertexPtr->_loopPtr, vertexPtr->_loopPtr->_loopEdgeLinkPtr, _newEdgePtr->_leftLinkPtr);
			insert_loop_edge_link(vertexPtr->_loopPtr, vertexPtr->_loopPtr->_loopEdgeLinkPtr, _newEdgePtr->_rightLinkPtr);
			//_newEdgePtr->_leftLinkPtr->_preLoopEdgeLinkPtr = _newEdgePtr->_rightLinkPtr;
			//_newEdgePtr->_rightLinkPtr->_nextLoopEdgeLinkPtr = _newEdgePtr->_leftLinkPtr;
		}
		else if (vertexPtr->_edgePtrVector.size() == 1) {
			insert_loop_edge_link((vertexPtr->_edgePtrVector[0])->_rightLinkPtr->_loopPtr, 
								 (vertexPtr->_edgePtrVector[0])->_rightLinkPtr, 
								_newEdgePtr->_rightLinkPtr);

			insert_loop_edge_link((vertexPtr->_edgePtrVector[0])->_leftLinkPtr->_loopPtr,
								 (vertexPtr->_edgePtrVector[0])->_leftLinkPtr,
								 _newEdgePtr->_leftLinkPtr);
			//_newEdgePtr->_leftLinkPtr->_preLoopEdgeLinkPtr = _newEdgePtr->_rightLinkPtr;
			//_newEdgePtr->_rightLinkPtr->_nextLoopEdgeLinkPtr = _newEdgePtr->_leftLinkPtr;
		}
		else if (vertexPtr->_edgePtrVector.size() == 2) {
			insert_loop_edge_link((vertexPtr->_edgePtrVector[0])->_rightLinkPtr->_loopPtr,
								(vertexPtr->_edgePtrVector[0])->_rightLinkPtr,
								_newEdgePtr->_rightLinkPtr);

			insert_loop_edge_link((vertexPtr->_edgePtrVector[0])->_rightLinkPtr->_loopPtr,
								(vertexPtr->_edgePtrVector[0])->_rightLinkPtr,
								_newEdgePtr->_leftLinkPtr);
		}
		else {
			//多于2个的情况暂时不处理，需要找到最外侧的两个边

		}
		connect_edge_to_vertex(_newEdgePtr);
	}

	//split an edge(inserting a vertex in an edge)
	void CVolumeObject::mev(AlphaModeller::CVertex * startVertexPtr, CEdge * edgePtr, CPoint * positionPtr)
	{
		AlphaModeller::CVertex *_newVertexPtr = add_vertex(this, *positionPtr);
		CEdge *_newEdge = new CEdge(startVertexPtr,
									_newVertexPtr,
								    edgePtr->_curvePtr);
		insert_loop_edge_link(edgePtr->_rightLinkPtr->_loopPtr,
							  edgePtr->_rightLinkPtr,
							  _newEdge->_rightLinkPtr);
		insert_loop_edge_link(edgePtr->_leftLinkPtr->_loopPtr,
							  edgePtr->_leftLinkPtr,
							  _newEdge->_leftLinkPtr);
		_newVertexPtr->_edgePtrVector.push_back(_newVertexPtr);
		_newVertexPtr->_edgePtrVector.push_back(edgePtr);

		CEdgePtrVector::iterator _edgePtrIterator;
		_edgePtrIterator = find(startVertexPtr->_edgePtrVector.begin(),
								startVertexPtr->_edgePtrVector.end(),edgePtr);
		startVertexPtr->_edgePtrVector.erase(_edgePtrIterator);
		startVertexPtr->_edgePtrVector.push_back(_newEdge);
	}

	/*
	//split an vertex(inserting an edge between two edges)
	void CVolumeObject::mev(AlphaModeller::CVertex * splitVertexPtr, CEdge * preEdgePtr, CEdge * nextEdgePtr, CPoint * position, CCurve * curPtr)
	{
		AlphaModeller::CVertex *_newVertexPtr = add_vertex(this, *position);
		CEdge *_newEdge = new CEdge(splitVertexPtr,
									_newVertexPtr,
									curPtr);

		insert_loop_edge_link(edgePtr->_rightLinkPtr->_loopPtr,
			edgePtr->_rightLinkPtr,
			_newEdge->_rightLinkPtr);
		insert_loop_edge_link(edgePtr->_leftLinkPtr->_loopPtr,
			edgePtr->_leftLinkPtr,
			_newEdge->_leftLinkPtr);
		_newVertexPtr->_edgePtrVector.push_back(_newVertexPtr);
		_newVertexPtr->_edgePtrVector.push_back(edgePtr);

		CEdgePtrVector::iterator _edgePtrIterator;
		_edgePtrIterator = find(startVertexPtr->_edgePtrVector.begin(),
			startVertexPtr->_edgePtrVector.end(), edgePtr);
		startVertexPtr->_edgePtrVector.erase(_edgePtrIterator);
		startVertexPtr->_edgePtrVector.push_back(_newEdge);
	}
	*/

	//only consider two vertexes in the same loop
	void CVolumeObject::mef(CShell*shellPtr,
							AlphaModeller::CVertex * startVertexPtr,
							AlphaModeller::CVertex * endVertexPtr,
							CEdge* startEdgePtr,
							CEdge* endEdgePtr,
							CCurve* curPtr,
							CSurface *surfacePtr)
	{
		CEdge *_newEdgePtr = new CEdge(startVertexPtr,endVertexPtr,curPtr);
		//connect the edge
		startEdgePtr->_rightLinkPtr->_nextLoopEdgeLinkPtr = _newEdgePtr->_rightLinkPtr;
		startEdgePtr->_leftLinkPtr->_nextLoopEdgeLinkPtr = _newEdgePtr->_leftLinkPtr;
		_newEdgePtr->_rightLinkPtr->_preLoopEdgeLinkPtr = startEdgePtr->_rightLinkPtr;
		_newEdgePtr->_leftLinkPtr->_preLoopEdgeLinkPtr = startEdgePtr->_leftLinkPtr;

		endEdgePtr->_rightLinkPtr->_preLoopEdgeLinkPtr = _newEdgePtr->_rightLinkPtr;
		endEdgePtr->_leftLinkPtr->_preLoopEdgeLinkPtr = _newEdgePtr->_leftLinkPtr;
		_newEdgePtr->_rightLinkPtr->_nextLoopEdgeLinkPtr = endEdgePtr->_rightLinkPtr;
		_newEdgePtr->_leftLinkPtr->_nextLoopEdgeLinkPtr = endEdgePtr->_leftLinkPtr;
		//bool _sameLoopMarker = true;
		CFace* _facePtr = new CFace(shellPtr,surfacePtr);
		CLoop* _loopPtr = _facePtr->new_loop();
		CLoopEdgeLink* _loopEdgeLinkPtrIterator = startEdgePtr->_rightLinkPtr;
		//给所有新的loop edge link的loop pointer赋值
		do
		{
			_loopEdgeLinkPtrIterator->_loopPtr = _loopPtr;
		} while (_loopEdgeLinkPtrIterator!=startEdgePtr->_rightLinkPtr);
		
		//CEdge *_newEdgePtr=_loopPtr->create_edge_with_loop(startVertexPtr, endVertexPtr, curPtr);

	}

	void CVolumeObject::kemr(CLoop * outLoop, CEdge * edge, AlphaModeller::CVertex * vertexOnOutLoop)
	{
	}

	void CVolumeObject::kfmhr(CFace * outFace, CFace * innerFace)
	{
	}

	AlphaModeller::CObjectGroup::CObjectGroup()
	{
	}

	AlphaModeller::CObjectGroup::~CObjectGroup()
	{
	}

	AlphaModeller::CVertex* add_vertex(CVolumeObject * objectPtr, CPoint &point)
	{
		objectPtr->_pointVector.push_back(point);
		AlphaModeller::CVertex *_vertexPtr = new AlphaModeller::CVertex(&(objectPtr->_pointVector.back()));
		return _vertexPtr;
	}

}

