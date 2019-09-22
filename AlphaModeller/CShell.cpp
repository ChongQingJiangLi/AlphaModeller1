#include "CShell.h"
#include"CObject.h"
#include <algorithm>
#include <vector>
AlphaModeller::CShell::CShell(CVolumeObject* objectPtr)
{
	_ownerObjectPtr = objectPtr;
	if (objectPtr != nullptr) { 
		objectPtr->connect_shell(this); //ÔÚobjectÖÐÌí¼Óshell
	}
}

AlphaModeller::CShell::~CShell()
{
	if (_shellID == _curID-1) { _curID--; }
	if (_ownerObjectPtr != nullptr) {
		_ownerObjectPtr;
	}
	for (auto &faceIterator : _facePtrVector) {
		delete faceIterator;
	}
}

void AlphaModeller::CShell::add_face(CFace * facePtr)
{
	facePtr->_shellPtr = this;
	_facePtrVector.push_back(facePtr);
}

void AlphaModeller::CShell::delete_face(CFace * facePtr)
{
	std::vector<CFace*>::iterator faceIterator; 
	faceIterator = std::find(_facePtrVector.begin(),_facePtrVector.end(),facePtr);
	if (faceIterator != _facePtrVector.end()) {
		_facePtrVector.erase(faceIterator);
	}
	facePtr->_shellPtr = nullptr;
}

AlphaModeller::CFace * AlphaModeller::CShell::new_face(CShell * shellPtr)
{
	CFace *_facePtr = new CFace(shellPtr);
	//this->_facePtrVector.push_back(_facePtr);
	return _facePtr;
}
