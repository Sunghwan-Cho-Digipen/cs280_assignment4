/******************************************************************
CopypRightTree (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: BSTree.hpp
Project: Assignment 4 - BST & AVL
Author: Kevin Wright, Sunghwan Cho
Creation date: 05/15/21
******************************************************************/

#include <string>
#include <list>
#include <iomanip>

#include "BSTree.h"

template <typename T>
BSTree<T>::BinTreeNode::BinTreeNode(const T& value)
	: pLeftTree(nullptr), pRightTree(nullptr), data(value), size(1)
{
}

template <typename T>
BSTree<T>::BinTreeNode::BinTreeNode(const BinTreeNode& rhs)
	: data(rhs.data), size(rhs.size)
{
	if(rhs.pLeftTree != nullptr)
	{
		pLeftTree = new BinTreeNode(*rhs.pLeftTree);
	}
	
	if(rhs.pRightTree != nullptr)
	{
		pRightTree = new BinTreeNode(*rhs.pRightTree);
	}
}

template <typename T>
BSTree<T>::BinTreeNode::~BinTreeNode()
{
	if (pLeftTree != nullptr)
	{
		delete pLeftTree;
		pLeftTree = nullptr;
	}
	if (pRightTree != nullptr)
	{
		delete pRightTree;
		pRightTree = nullptr;
	}
}

template<typename T>
const T& BSTree<T>::BinTreeNode::operator[](unsigned int index) const
{
	unsigned int leftMaxIndex = 0;
	if (pLeftTree != nullptr)
	{
		leftMaxIndex = pLeftTree->size;
	}
	if (index < leftMaxIndex)
	{
		return (*pLeftTree)[index];
	}
	if (index == leftMaxIndex)
	{
		return data;
	}
	if (pRightTree != nullptr)
	{
		return (*pRightTree)[index - leftMaxIndex - 1];
	}

	throw BSTException("Out of Range");
}

template <typename T>
void BSTree<T>::BinTreeNode::Insert(const T& value)
{
	++size;
	if(value >= data)
	{
		if (pRightTree != nullptr)
		{
			pRightTree->Insert(value);
		}
		else
		{
			pRightTree = new BinTreeNode(value);;
		}
		return;
	}
	else if(value < data)
	{
		if (pLeftTree != nullptr)
		{
			pLeftTree->Insert(value);
		}
		else
		{
			pLeftTree = new BinTreeNode(value);
		}
	}
}

template <typename T>
bool BSTree<T>::BinTreeNode::Remove(BinTreeNode*& root, BinTreeNode* parentPtr, const T& value)
{
	// I don't know if this is right way to be done, but it seems too nasty code.....
	
	if (data < value)
	{
		if(pRightTree == nullptr)
		{
			return false;
		}

		BinTreeNode* targetNode = pRightTree;
		const bool isGoingToBeRemoved = pRightTree->Remove(root, this, value);
		if (isGoingToBeRemoved == true)
		{
			--size;
			if (targetNode->data == value)
			{
				delete targetNode;
			}
		}
		return isGoingToBeRemoved;
	}
	else if (data > value)
	{
		if (pLeftTree == nullptr)
		{
			return false;
		}

		BinTreeNode* targetNode = pLeftTree;
		const bool isGoingToBeRemoved = pLeftTree->Remove(root, this, value);

		if (isGoingToBeRemoved == true)
		{
			--size;
			if (targetNode->data == value)
			{
				delete targetNode;
			}
		}
		return isGoingToBeRemoved;
	}

	if (pLeftTree != nullptr && pRightTree != nullptr)
	{
		--size;
		data = pLeftTree->FindLargest();

		BinTreeNode* targetNode = pLeftTree;
		const bool isGoingToBeRemoved = pLeftTree->Remove(root, this, data);
		if (isGoingToBeRemoved == true)
		{
			if (targetNode->data == data)
			{
				delete targetNode;
			}
		}
		return true;
	}
	else if (pRightTree != nullptr || pLeftTree != nullptr)
	{
		--size;
		BinTreeNode* targetNode = (pLeftTree == nullptr ? pRightTree : pLeftTree);

		if (root == this)
		{
			root = targetNode;
			pLeftTree = pRightTree = nullptr;
			return true;
		}
		
		parentPtr->pLeftTree == this ? parentPtr->pLeftTree = targetNode : parentPtr->pRightTree = targetNode;

		pLeftTree = pRightTree = nullptr;
		return true;
	}
	else if (pRightTree == nullptr && pLeftTree == nullptr)
	{
		--size;
		if (root == this)
		{
			root = nullptr;
			return true;
		}

		parentPtr->pLeftTree == this ? parentPtr->pLeftTree = nullptr : parentPtr->pRightTree = nullptr;
		
		return true;
	}

	
	return false;
}

template <typename T>
int BSTree<T>::BinTreeNode::Height() const
{
	const int leftHeight = (pLeftTree == nullptr) ? -1 : pLeftTree->Height();
	const int rightHeight = (pRightTree == nullptr) ? -1 : pRightTree->Height();

	return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

template <typename T>
bool BSTree<T>::BinTreeNode::Find(const T& value)
{
	if(data == value)
	{
		return true;
	}
	
	const bool isFoundInLeft = pLeftTree != nullptr ? pLeftTree->Find(value) : false;
	const bool isFoundInRight = pRightTree != nullptr ? pRightTree->Find(value) : false;
	
	return isFoundInLeft || isFoundInRight;
}

template <typename T>
T BSTree<T>::BinTreeNode::FindLargest()
{
	if(pRightTree != nullptr)
	{
		return pRightTree->FindLargest();
	}
	return data;
}

template <typename T>
BSTree<T>::BSTree(): pRootNode(nullptr)
{
	
}

template <typename T>
BSTree<T>::BSTree(const BSTree& rhs)
{
	if (rhs.pRootNode != nullptr)
	{
		pRootNode = new BinTreeNode(*rhs.pRootNode);
	}
}

template <typename T>
BSTree<T>::~BSTree()
{
	Clear();
}

template <typename T>
BSTree<T>& BSTree<T>::operator=(const BSTree& rhs)
{
	Clear();
	pRootNode = rhs.pRootNode;
	return *this;
}

template<typename T>
const T& BSTree<T>::operator[](unsigned int index) const
{
	return (*pRootNode)[index];
}

template <typename T>
void BSTree<T>::Insert(const T& value)
{
	if (IsEmpty() == true)
	{
		pRootNode = new BinTreeNode(value);
		return;
	}
	pRootNode->Insert(value);
}

template <typename T>
void BSTree<T>::Remove(const T& value)
{
	if(pRootNode == nullptr)
	{
		throw BSTException("Item was not found");
	}

	BinTreeNode* targetNode = pRootNode;
	const bool didValueRemoved = pRootNode->Remove(pRootNode, nullptr, value);
	if(didValueRemoved == false)
	{
		throw BSTException("Item was not found");
	}
	if(targetNode != pRootNode)
	{
		delete targetNode;
	}
}

template <typename T>
bool BSTree<T>::IsEmpty() const
{
	return pRootNode == nullptr;
}

template <typename T>
unsigned BSTree<T>::Size() const
{
	return pRootNode->size;
}

template <typename T>
int BSTree<T>::Height() const
{
	return pRootNode == nullptr ? -1 : pRootNode->Height();
}

template <typename T>
void BSTree<T>::Clear()
{
	if (pRootNode != nullptr)
	{
		delete pRootNode;
		pRootNode = nullptr;
	}
}

template <typename T>
bool BSTree<T>::Find(const T& value) const
{
	if(IsEmpty() == true)
	{
		return false;
	}
	
	return pRootNode->Find(value);
}

template <typename T>
void BSTree<T>::ResetRoot()
{
	pRootNode = nullptr;
}

template <typename T>
std::queue<typename BSTree<T>::BinTreeNode*> BSTree<T>::CreatePrintQueue() const
{
	std::queue<typename  BSTree<T>::BinTreeNode*> returnValue;
	const int height = pRootNode->Height();
	for (int depth = 0; depth <= height; ++depth)
	{
		CreatePrintQueueByDepth(pRootNode, returnValue, depth);
	}
	return returnValue;
}

template <typename T>
void BSTree<T>::CreatePrintQueueByDepth(BinTreeNode* root, std::queue<BinTreeNode*>& printQueue, int depth) const
{
	if(depth == 0)
	{
		printQueue.push(root);
	}
	else if(depth > 0)
	{
		if(root != nullptr)
		{
			CreatePrintQueueByDepth(root->pLeftTree, printQueue, depth - 1);
			CreatePrintQueueByDepth(root->pRightTree, printQueue, depth - 1);
		}
		else
		{
			CreatePrintQueueByDepth(nullptr, printQueue, depth - 1);
			CreatePrintQueueByDepth(nullptr, printQueue, depth - 1);
		}
	}
}

template<typename T>
void BSTree<T>::DebugPrint(bool showCounts) const {

	if (pRootNode != nullptr) {
		std::queue<BinTreeNode*> printQueue = CreatePrintQueue();
		std::queue<BinTreeNode*> showCountQueue;
		if (showCounts) {
			showCountQueue = printQueue;
		}

		std::cout << "height: " << pRootNode->Height();
		std::cout << ", nodes: " << pRootNode->size << std::endl;

		int nodeRowCount = 0;
		int nodeRowTarget = 1;
		int coutWidth = 2 << pRootNode->Height();
		while (printQueue.empty() == false) {
			if (nodeRowCount == 0) {
				std::cout.width(coutWidth / 2); // first node of each row should have a 1/2 width offset
			} else {
				std::cout.width(coutWidth - 1);	// set the width for the next element
			}

			if (printQueue.front() != nullptr) {
				std::cout << printQueue.front()->data;
			} else {
				std::cout << "X";
			}

			// check if we are done with the current row
			if (++nodeRowCount == nodeRowTarget) {
				std::cout << std::endl;
				nodeRowTarget *= 2;
				coutWidth /= 2;
				nodeRowCount = 0;
			} else {
				std::cout << ' ';
			}
			printQueue.pop();
		}
		if (showCounts) {
			while (showCountQueue.empty() == false) {
				if (showCountQueue.front() != nullptr) {
					std::cout << showCountQueue.front()->data << "(" << showCountQueue.front()->size << ")  ";
				}
				showCountQueue.pop();
			}
			std::cout << std::endl;
		}
	} else {
		std::cout << "Tree is Empty" << std::endl;
	}
	std::cout << std::endl;
}
