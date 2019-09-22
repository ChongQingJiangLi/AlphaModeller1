#pragma once
#include <Eigen/Dense>

namespace AlphaModeller {
	class CSpace
	{
	public:
		Eigen::Vector3d _minPos,_maxPos;

	public:
		CSpace(const double xMin, const double yMin, const double zMin, const double xMax, const double yMax, const double zMax);
		CSpace(const Eigen::Vector3d _minPos, const Eigen::Vector3d _maxPos);

		~CSpace();
	};
}






