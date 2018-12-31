// Binary Search Tree ADT
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Edward Chen and Mauricio Nunez
 
#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{   
private:
	// internal insert node: insert newNode in nodePtr subtree
	BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);
   
	// internal remove node: locate and delete target node under nodePtr subtree
	BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool & success);

	void _getEntry2(BinaryNode<ItemType>* treePtr, const ItemType & target) const;
   
	// delete target node from tree, called by internal remove node
	BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);
   
	// remove the leftmost node in the left subtree of nodePtr
	BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType & successor);
   
	// search for target node
	BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, const ItemType & target) const;
	// search for target node
	

	// search for smallest node
	BinaryNode<ItemType>* findSmallest(BinaryNode<ItemType>* treePtr) const;

	// search for largest node
	BinaryNode<ItemType>* findLargest(BinaryNode<ItemType>* treePtr) const;

public:  
	// insert a node at the correct location
    bool insert(const ItemType & newEntry);
	// remove a node if found
	bool remove(const ItemType & anEntry);
	// find a target node
	bool getEntry(const ItemType & target, ItemType & returnedItem) const;
	// find all target nodes
	void getEntry2(const ItemType & target) const;
	// find the smallest node
	bool getSmallest(ItemType & returnedSmallest) const;
	// find the largest node
	bool getLargest(ItemType & returnedLargest) const;
};


///////////////////////// public function definitions ///////////////////////////

// Uses _insert internal function
template<class ItemType>
bool BinarySearchTree<ItemType>::insert(const ItemType & newEntry)
{
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
	this->rootPtr = _insert(this->rootPtr, newNodePtr);
	return true;
}  

// Uses _remove internal function
template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType & target)
{
	bool isSuccessful = false;
	this->rootPtr = _remove(this->rootPtr, target, isSuccessful);
	return isSuccessful; 
}  

// Uses findNode internal function to locate the value and returns false if not found
template<class ItemType>
bool BinarySearchTree<ItemType>::getEntry(const ItemType& anEntry, ItemType & returnedItem) const
{
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(returnedItem);
	newNodePtr = findNode(this->rootPtr, anEntry);
	if (newNodePtr == NULL) {
		return false;
	}
	returnedItem = newNodePtr->getItem();
	return true;
}  

// Uses findNode internal function to locate all values and print them
template<class ItemType>
void BinarySearchTree<ItemType>::getEntry2(const ItemType& anEntry) const
{
	_getEntry2(this->rootPtr, anEntry);
}

// Uses findSmallest internal function
template<class ItemType>
bool BinarySearchTree<ItemType>::getSmallest(ItemType& returnedSmallest) const
{
	BinaryNode<ItemType>* nodePtr = new BinaryNode<ItemType>(returnedSmallest);
	nodePtr = findSmallest(this->rootPtr);
	returnedSmallest = nodePtr->getItem();
	return true;
}

// Uses findLargest internal function
template<class ItemType>
bool BinarySearchTree<ItemType>::getLargest(ItemType& returnedLargest) const
{
	BinaryNode<ItemType>* nodePtr = new BinaryNode<ItemType>(returnedLargest);
	nodePtr = findLargest(this->rootPtr);
	returnedLargest = nodePtr->getItem();
	return true;
}
//////////////////////////// private functions ////////////////////////////////////////////

// Inserts the new node into the tree by using iteration
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr,
                                                          BinaryNode<ItemType>* newNodePtr)
{
	BinaryNode<ItemType>* pWalk;
	BinaryNode<ItemType>* parent = NULL;
	if(nodePtr == NULL)
	{
		nodePtr = newNodePtr;
	}
	else {
		pWalk = nodePtr;
		while (pWalk != NULL) {
			parent = pWalk;
			if (newNodePtr->getItem().returnKey() < pWalk->getItem().returnKey()) {
				pWalk = pWalk->getLeftPtr();
			}
			else {
				pWalk = pWalk->getRightPtr();
			}
		}
		if (newNodePtr->getItem().returnKey() < parent->getItem().returnKey()) {
			parent->setLeftPtr(newNodePtr);
		}
		else {
			parent->setRightPtr(newNodePtr);
		}
	}
	return nodePtr;
}  

// Removes node from tree, uses deleteNode
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr,
                                                          const ItemType target,
                                                          bool & success)
{
	if (nodePtr == NULL)                   
	{
		success = false;
		return 0;
	}
	if (nodePtr->getItem().returnKey() > target.returnKey())
		nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
	else if (nodePtr->getItem().returnKey() < target.returnKey())
		nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
	else		
	{
		nodePtr = deleteNode(nodePtr);
		success = true;
	}      
	return nodePtr;   
}  

// Locates the node for findEntry
template<class ItemType>
void BinarySearchTree<ItemType>::_getEntry2(BinaryNode<ItemType>* nodePtr,
	const ItemType & target) const
{
	if (nodePtr == NULL)
		return;
	if (nodePtr->getItem().returnKey() == target.returnKey()) {
		cout << nodePtr->getItem().returnName() << " has this tuition" << endl;
	}

	_getEntry2(nodePtr->getRightPtr(), target);
	// Key is smaller than root's key 
	_getEntry2(nodePtr->getLeftPtr(), target);
}

// Deletes node
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::deleteNode(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr->isLeaf())				
	{
		delete nodePtr;
		nodePtr = 0;
		return nodePtr;
	}
	else if (nodePtr->getLeftPtr() == 0)  
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else if (nodePtr->getRightPtr() == 0) 
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;      
	}
	else                                  
	{
		ItemType newNodeValue;
		nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
		nodePtr->setItem(newNodeValue);
		return nodePtr;
	}  
}  

// Removes left-most node
template<class ItemType> 
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
                                                                     ItemType & successor)
{
	if (nodePtr->getLeftPtr() == 0)
	{
		successor = nodePtr->getItem();
		return deleteNode(nodePtr);
	}
	else 
	{
		nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
		return nodePtr;
	}       
}

// Locates the node for findEntry
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* nodePtr,
                                                           const ItemType & target) const 
{
	if (nodePtr == NULL || nodePtr->getItem().returnKey() == target.returnKey())
		return nodePtr;

	if (nodePtr->getItem().returnKey() < target.returnKey())
		return findNode(nodePtr->getRightPtr(), target);
	// Key is smaller than root's key 
	return findNode(nodePtr->getLeftPtr(), target);
}

// Finds smallest node
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findSmallest(BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr == nullptr)
	{
		return nullptr;
	}
	else if (nodePtr->getLeftPtr() == nullptr)
	{
		return nodePtr;
	}
	else
	{
		return findSmallest(nodePtr->getLeftPtr());
	}
}

// Finds largest node
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findLargest(BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr == nullptr)
	{
		return nullptr;
	}
	else if (nodePtr->getRightPtr() == nullptr)
	{
		return nodePtr;
	}
	else
	{
		return findLargest(nodePtr->getRightPtr());
	}
}
#endif
