#pragma once
#include <Eigen/Dense>



namespace AlphaModeller {
	class CPoint
	{
	public:
		Eigen::Vector3d _position;
		//pointer to a vertex or supplementary geometry entity using the point
		//information list pointer
		//pointer to the head of a chain of group links to the groups containing the vertex
		unsigned int _markerBits = 0;//marker bits for modelling operations
		unsigned int _pointID = 0;//point ID
		unsigned int _refNum = 0;//


	public:
		CPoint(const double x, const double y, const double z);
		~CPoint();
	};
}

