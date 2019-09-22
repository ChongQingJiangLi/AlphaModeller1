#include "pch.h"
#include "CPoint.h"


namespace AlphaModeller {
	CPoint::CPoint(const double x, const double y, const double z)
	{
		_position(0) = x;
		_position(1) = y;
		_position(2) = z;
	}


	CPoint::~CPoint()
	{
	}
}
