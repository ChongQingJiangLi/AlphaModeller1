#pragma once
#include "CObject.h"
namespace AlphaModeller {

	class CShell {

		// data
	public:
		CObject *_ownerObjectPtr = nullptr;
		CShell *_nextShellPtr = nullptr;
		unsigned int _markerBits = 0;
		unsigned int _shellID = 0;
		CSpace* _spacePtr=nullptr;
		std::vector<CFace*> _facePtrVector;
		//information list pointer
		//pointer to the head of a chain of group links to the groups containing the loop
		//pointer to the name of the shell

		//operation
	public:
		CShell(CVolumeObject *objectPtr) :_shellID(_curID++) {};
		~CShell();
		void add_face(CFace *facePtr);
		void delete_face(CFace *facePtr);
		CFace *new_face(CShell* shellPtr);
	private:
		static unsigned long long int _curID;
	};



}