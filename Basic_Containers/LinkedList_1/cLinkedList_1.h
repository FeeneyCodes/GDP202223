#pragma once
#include <string>

class cLinkedList_1
{
private:
	struct sNode
	{
//		sNode() { nextIndex = NULL; previousIndex = NULL;  }
		std::string theData;
		sNode* pNextNode = NULL;
		sNode* pPreviousNode = NULL;
	};
public:
	cLinkedList_1();
	~cLinkedList_1();

	void moveToHead(void);	// head or start

	void moveNext(void);
	void movePrevious(void);

	bool isAtHead(void);
	bool isAtTail(void);

	// Inserts after wherever we are pointing currently
	void insert(std::string theData);			
	std::string getValue(void);	// At the current location
	//std::string getAtIndex(int index);

private:
	//std::string myData[1000];
	//std::string* m_pMyData;
	sNode* m_pMyData;	// point to the root or head or start

	sNode* m_pCurrent;	// points to the "current" node (we are looking at)

};

