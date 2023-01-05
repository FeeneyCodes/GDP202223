#include "cLinkedList_1.h"

cLinkedList_1::cLinkedList_1()
{
	// At start, there isn't any data
	this->m_pMyData = NULL;
	this->m_pCurrent = NULL;
}

cLinkedList_1::~cLinkedList_1()
{
}

// head or start
void cLinkedList_1::moveToHead(void)
{
	// Point the current node to the start of the data (1st node)
	this->m_pCurrent = this->m_pMyData;
}

void cLinkedList_1::moveNext(void)
{
}

void cLinkedList_1::movePrevious(void)
{
}

bool cLinkedList_1::isAtHead(void)
{
	//TODO: Amazing code here
	return true;
}

bool cLinkedList_1::isAtTail(void)
{
	// Is there any data? 
	if ( this->m_pMyData == NULL )
	{
		// TODO: Take another poll to see what the class wants...
		// If there's nothing, then we are at the tail, sort of...
		return true;
	}

	// Is the current nodes "next" node == NULL?
	if ( this->m_pCurrent->pNextNode == NULL )
	{
		return true;
	}
	// Or we aren't
	return false;
}

// Insert at current location
void cLinkedList_1::insert(std::string theDataToInsert)
{
	// Is there any data there, yet?
	if (this->m_pMyData == NULL )
	{
		// Nope. Nadda. Nothing. The Eternal Void. 
		sNode* pNewNode = new sNode();

		// Set data and update next and previous
		pNewNode->theData = theDataToInsert;
		// There aren't any other nodes, so they can be NULL
		pNewNode->pNextNode = NULL;
		pNewNode->pPreviousNode = NULL;

		// Add this 1st node
		this->m_pMyData = pNewNode;
		// Point the current node to this node
		this->m_pCurrent = pNewNode;
	}
	else
	{
		// There is already some data
		// Hazzah Democracy: 
		// Replace, move to tail: 
		// 	Add after : 3
		//	I don't care: 2
		//	What are we doing ?
		//	They are both awesome!1

		sNode* pNewNode = new sNode();
		pNewNode->theData = theDataToInsert;

		// Connect this node to the other nodes
		// Point the "current" node's "prior" node to this new node

		// Save the current node's old pointers
		sNode* pOG_NextNode = this->m_pCurrent->pNextNode;
		sNode* pOG_PreviousNode = this->m_pCurrent->pPreviousNode;

		// Point current node to the new node
		this->m_pCurrent->pNextNode = pNewNode;
		// Point the new node back to the current node
		pNewNode->pPreviousNode = this->m_pCurrent;

		// Current nodes old "next" points to new node
		if ( pOG_NextNode != NULL )
		{
			pOG_NextNode->pPreviousNode = pNewNode;
		}

		// New nodes "next" is pointing to old current nodes next node
		pNewNode->pNextNode = pOG_NextNode;

		// Point "current" node to the one we just added
		this->m_pCurrent = pNewNode;

	}

	return;
}

	// At the current location
std::string cLinkedList_1::getValue(void)
{
	if ( this->m_pMyData == NULL )
	{
		// TODO: What do we do here??? 
		// Throw an exception? Return nothing?? 
		return "";
	}
	
	return this->m_pCurrent->theData;
}