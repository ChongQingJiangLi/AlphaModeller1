#pragma once
#include"CSpace.h"
namespace AlphaModeller {
	class CSurface
	{
		//data
	public:
		CSurfaceType *_surfaceTypePtr;
		//pointer to an edge ot supplementary geometry entity using the surface
		//information list pointer
		//pointer to the head of a chain of group links to the groups containing the curve
		CSpace *_spacePtr;
		unsigned int _markerBits = 0;//marker bits for modelling operations
		unsigned int _surfaceID = 0;//point ID
		unsigned int _refNum = 0;//

		//operation
	public:
		CSurface();
		~CSurface();
	};

	class CSurfaceType {
		//data
	public:
		enum SurfaceType { PLANE,SPHERE,CYLINDER,CONE,QUADRIC,TOROID,FF_SURF};
		SurfaceType _surfaceType;
		//operation
	public:
		CSurfaceType();
		~CSurfaceType();

	};
	class CPlaneSurface :public CSurfaceType {
		//data
	public:
		
		//operation
	public:
		CPlaneSurface();
		~CPlaneSurface();

	};
}