#pragma once
#include "CSpace.h"
namespace AlphaModeller {
	class CCurveType {
		//data
	public:
		enum CurveType { STRAIGHT, CIRCLE, ELLIPSE, PARABOLA, HYPERBOLA, FREEFORMCURVE };
		CurveType _curveType;
		//operation
	public:
		CCurveType();
		~CCurveType();

	};

	class CCurve
	{
		//data
	public:
		CCurveType *curveTypePtr;
		//pointer to an edge ot supplementary geometry entity using the curve
		//information list pointer
		//pointer to the head of a chain of group links to the groups containing the curve
		CSpace *spacePtr;
		unsigned int _markerBits = 0;//marker bits for modelling operations
		unsigned int _curveID = 0;//point ID
		unsigned int _refNum = 0;//

		//operation
	public:
		CCurve();
		~CCurve();
	};

	
	class CStraightCurve :public CCurveType {
		//data
	public:
		CurveType _curveType;
		//operation
	public:
		CStraightCurve();
		~CStraightCurve();


	};

}

