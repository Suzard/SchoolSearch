// Binary tree abstract base class
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Edward Chen
 
#ifndef _BINARY_TREE
#define _BINARY_TREE
#include <iostream>
using namespace std;
#include "BinaryNode.h"
#include "Queue.h"
#include <map>
template<class ItemType>
class BinaryTree
{
protected:
	BinaryNode<ItemType>* rootPtr;		// ptr to root node
	int count;							// number of nodes in tree

public:
	// "admin" functions
 	BinaryTree() {rootPtr = 0; count = 0;}
	BinaryTree(const BinaryTree<ItemType> & tree){ }
	virtual ~BinaryTree() { }
	BinaryTree & operator = (const BinaryTree & sourceTree);
   
	// common functions for all binary trees
 	bool isEmpty() const	{return count == 0;}
	int size() const	    {return count;}
	void clear()			{destroyTree(rootPtr); rootPtr = 0; count = 0;}
	void preOrder(void visit(ItemType &)) const {_preorder(visit, rootPtr);}
	void inOrder(void visit(ItemType &)) const  {_inorder(visit, rootPtr);}
	void postOrder(void visit(ItemType &)) const{_postorder(visit, rootPtr);}
	//new functions
	void breadthFirst(void visit(ItemType &)) const { _breadthFirst(visit, rootPtr); }
	map<int, int> indentOrder() const { return _indentOrder(rootPtr); }
	void printIndented() const { _printIndented(rootPtr, _indentOrder(rootPtr)); }

	// abstract functions to be implemented by derived class
	virtual bool insert(const ItemType & newData) = 0; 
	virtual bool remove(const ItemType & data) = 0; 
	virtual bool getEntry(const ItemType & anEntry, ItemType & returnedItem) const = 0;

private:   
	// delete all nodes from the tree
	void destroyTree(BinaryNode<ItemType>* nodePtr);

	// copy from the tree rooted at nodePtr and returns a pointer to the copy
	BinaryNode<ItemType>* copyTree(const BinaryNode<ItemType>* nodePtr);

	// internal traverse
	void _preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	//new functions
	void _breadthFirst(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	map<int, int> _indentOrder(BinaryNode<ItemType>* nodePtr) const;
	void _printIndented(BinaryNode<ItemType>* nodePtr, map<int, int> Level) const;

}; 

//////////////////////////////////////////////////////////////////////////

template<class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::copyTree(const BinaryNode<ItemType>* nodePtr) 
{
	BinaryNode<ItemType>* newNodePtr = 0;
    return newNodePtr;
}
  
// Traverses throught the tree and destroys all nodes.
template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		destroyTree(nodePtr->getLeftPtr());
		destroyTree(nodePtr->getRightPtr());
		cout << "Node deleted: "  << nodePtr->getItem().returnKey() << endl;
		remove(item);
	}
}  

// Preorder traversal
template<class ItemType>
void BinaryTree<ItemType>::_preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		visit(item);		
		_preorder(visit, nodePtr->getLeftPtr());
		_preorder(visit, nodePtr->getRightPtr());
	} 
}  
// Inorder traversal
template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		_inorder(visit, nodePtr->getLeftPtr());
		visit(item);
		_inorder(visit, nodePtr->getRightPtr());
	}
}

// Postorder traversal
template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		_postorder(visit, nodePtr->getLeftPtr());
		_postorder(visit, nodePtr->getRightPtr());
		visit(item);
	}
}  

// Breadth-First traversal
template<class ItemType>
void BinaryTree<ItemType>::_breadthFirst(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	std::map<int, string> mapOfLevelCount;
	if (nodePtr == NULL) {
		cout << "empty heap" << endl;
	}
	Queue<BinaryNode<ItemType>*> inQ;
	inQ.enqueue(nodePtr);
	int count = inQ.getCount();
	int level = 0;
	int inner_count = 0;
	for (count; count > 0; count = inQ.getCount()) {

		int count = inQ.getCount();
		if (inner_count != count)
			level += 1;
		inner_count = count;
		for (inner_count; inner_count > 0; inner_count--) {
			BinaryNode<ItemType>* current;
			inQ.dequeue(current);
			ItemType item = current->getItem();
			string id = std::to_string(item.returnKey());
			mapOfLevelCount[level] = mapOfLevelCount[level] + " [" + id + "]";
			if (current->getLeftPtr() != NULL) {
				inQ.enqueue(current->getLeftPtr());
			}
			if (current->getRightPtr() != NULL) {
				inQ.enqueue(current->getRightPtr());
			}
		}
	}
	for (std::pair<int, string> element : mapOfLevelCount) {
		// Accessing KEY from element
		std::string word = element.second;
		// Accessing VALUE from element.
		int count = element.first;
		std::cout << count << " :: " << word << std::endl;
	}
	int indent = mapOfLevelCount.size();
	//std::map<int, string>::reverse_iterator rit;
	//for (rit = mapOfLevelCount.rbegin(); rit != mapOfLevelCount.rend(); ++rit)
	//	std::cout << rit->first << " => " << rit->second << '\n';
}

// Helper function for printing the indented list
template<class ItemType>
map<int, int> BinaryTree<ItemType>::_indentOrder(BinaryNode<ItemType>* nodePtr) const
{
	std::map<int, int> mapOfLevelCount;
	if (nodePtr == NULL)
		return mapOfLevelCount;
	Queue<BinaryNode<ItemType>*> inQ;
	inQ.enqueue(nodePtr);
	int count = inQ.getCount();
	int inner_count = 0;
	int level = 0;
	for (count; count > 0; count = inQ.getCount()) {

		int count = inQ.getCount();
		if (inner_count != count)
			level += 1;
		inner_count = count;
		for (inner_count; inner_count > 0; inner_count--) {
			BinaryNode<ItemType>* current;
			inQ.dequeue(current);
			ItemType item = current->getItem();
			int id = item.returnKey();
			mapOfLevelCount[id] = level;
			if (current->getLeftPtr() != NULL) {
				inQ.enqueue(current->getLeftPtr());
			}
			if (current->getRightPtr() != NULL) {
				inQ.enqueue(current->getRightPtr());
			}
		}
	}
	return mapOfLevelCount;
}

// Prints the indented list using Inorder traversal
template<class ItemType>
void BinaryTree<ItemType>::_printIndented(BinaryNode<ItemType>* nodePtr, map<int, int> Level) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		_printIndented(nodePtr->getRightPtr(), Level);
		int key = item.returnKey();
		int level = Level[key]-1;
		string stuff(level, '\t');
		cout << stuff << level << "." << key << endl;
		_printIndented(nodePtr->getLeftPtr(), Level);
	}

}

template<class ItemType>
BinaryTree<ItemType> & BinaryTree<ItemType>::operator=(const BinaryTree<ItemType> & sourceTree)
{

}  
#endif

