#include "pch.h"
#include "CLoopEdgeLink.h"



AlphaModeller::CLoopEdgeLink::~CLoopEdgeLink()
{
}

AlphaModeller::CLoopEdgeLink * AlphaModeller::CLoopEdgeLink::find_opposite_loop_edge_link()
{
	return this->_edgePtr->_rightLinkPtr==this?this->_edgePtr->_leftLinkPtr:this->_edgePtr->_rightLinkPtr;
}


