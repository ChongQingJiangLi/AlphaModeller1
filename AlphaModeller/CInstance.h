#pragma once
#include "CObject.h"
#include <Eigen/Dense>

namespace AlphaModeller {

	class CInstance {
		//data
	public:
		CObject *_objectPtr=nullptr;
		CObjectGroup *_ownerObjectGroupPtr = nullptr;
		CInstance *_nextInstantancePtr = nullptr;
		CSpace *_spacePtr = nullptr;
		unsigned int _markerBits = 0;
		unsigned int _instanceID = 0;
		Eigen::Transform<double, 3, Eigen::Affine> *_transformPtr;//
		//pointer to a list of information elements associated with the edge
		//pointer to the head of a chain of group links to the groups containing the object

		//operation
	public:
		CInstance();
		~CInstance();
	
	};
}





