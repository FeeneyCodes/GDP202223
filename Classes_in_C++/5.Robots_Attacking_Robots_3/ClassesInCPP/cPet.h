#pragma once

//#include "cOwner.h"
class cOwner;	// Forward declaration

class cPet
{
public:
	cPet();

	void Walk(void);

	void CuddleOwner(void);

	void SetOwner(cOwner* pMyOwner);

private:
	cOwner* m_pMyOwner;		// Heap (it's a pointer)
};
