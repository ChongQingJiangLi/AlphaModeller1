#pragma once
#include "CLoop.h"
#include "CSurface.h"
#include "CShell.h"
#include "CObject.h"
#include "CSpace.h"
#include <vector>

namespace AlphaModeller {

	class CFace {
	public:
		CLoop* _loopPtr = nullptr;//pointer to the 
		CSurface* _surfacePtr = nullptr;//pointer to the surface of the face
		//CFaceGroup *_ownerFaceGroupPtr = nullptr;//pointer to the face group owning the face
		CShell* _shellPtr = nullptr;
		CFace* _nextFacePtr = nullptr;//pointer to the next face in the facegroup
		CFace* _preFacePtr = nullptr;//pointer to the pre face in the facegroup
		CFace* _friendFacePtr = nullptr;//for associating faces
		int _markerBits = 0;//marker bits for modelling operations
		std::vector<CLoop*> _loopPtrVector;
		unsigned int _faceID;//face ID

		//information list pointer
		//pointer to the head of a chain of group links to the groups containing the vertex

	//operation
	public:
		CFace(CShell* shellPtr) :_faceID(_curID++) 
		{
			_shellPtr = shellPtr;
			if (shellPtr != nullptr) {
				shellPtr->_facePtrVector.push_back(this);
			}
		};
		CFace(CShell* shellPtr, CSurface* surfacePtr) :_faceID(_curID++),_shellPtr(shellPtr), _surfacePtr(surfacePtr) 
		{
			if (shellPtr) { shellPtr->_facePtrVector.push_back(this); }
		};
		~CFace() ;
		void delete_loop(CLoop* loopPtr);
		CLoop* new_loop(CFace* facePtr);
		CLoop* new_loop();
		void connect_loop(CLoop* loopPtr);
		void disconnect_loop(CLoop* loopPtr);

	private:
		static unsigned long long int _curID;
	};




	class CFaceGroup {
		//data
	public:
		CFace *_facePtr=nullptr;//pointer to the first face in the facegroup
		CFaceGroup *_firstFaceGroup=nullptr;//pointer to the first facegroup in the facegroup
		CFaceGroup *_nextFaceGroup = nullptr;
		//a pointer to the shell or facegroup that owns the facegroup
		CSurface *_surfacePtr = nullptr;
		//pointer to a face, facegroup, or supplementary geometry entity using the same surface
		//pointer to a list of information elements associated with the edge
		//pointer to the head of a chain of group links to the groups containing the facegroup
		CSpace *_spacePtr = nullptr;
		unsigned int _markerBits = 0;//marker bits for modelling operations
		unsigned int _faceGroupID;//vertex ID
		//pointer to the name of the facegroup

		//operation
	public:
		CFaceGroup();
		~CFaceGroup();

	};


}