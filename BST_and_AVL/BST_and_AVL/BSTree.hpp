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
	: pLeftTree(nullptr), pRightTree(nullptr), data(value), size(0)
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
	delete pLeftTree;
	pLeftTree = nullptr;
	delete pRightTree;
	pRightTree = nullptr;
}

template<typename T>
const T& BSTree<T>::BinTreeNode::operator[](unsigned int index) const
{
	// TODO: insert return statement here
	
}

template <typename T>
void BSTree<T>::BinTreeNode::Insert(const T& value)
{
	if(value > data)
	{
		++size;
		if (pRightTree != nullptr)
		{
			pRightTree->Insert(value);
		}
		else
		{
			BinTreeNode* newBinTreeNode = new BinTreeNode(value);
			pRightTree = newBinTreeNode;
		}
	}
	else if(value < data)
	{
		++size;
		if (pLeftTree != nullptr)
		{
			pLeftTree->Insert(value);
		}
		else
		{
			BinTreeNode* newBinTreeNode = new BinTreeNode(value);
			pLeftTree = newBinTreeNode;
		}
	}
	else
	{
		throw BSTException("Value is same");
	}
}

template <typename T>
bool BSTree<T>::BinTreeNode::Remove(BinTreeNode*& root, BinTreeNode* parentPtr, const T& value)
{
	if (root->Find(value) == true)
	{

		if (pLeftTree != nullptr && pRightTree != nullptr)
		{

		}
		else if (pRightTree != nullptr || pLeftTree != nullptr)
		{

		}
		else if (pRightTree == nullptr && pLeftTree == nullptr)
		{

		}
	}
	
	return false;
}

template <typename T>
int BSTree<T>::BinTreeNode::Height() const
{
	const int leftHeight = (pLeftTree == nullptr) ? -1 : pLeftTree->Height();
	const int rightHeight = (pRightTree == nullptr) ? -1 : pRightTree->Height();

	return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
}

template <typename T>
bool BSTree<T>::BinTreeNode::Find(const T& value)
{
	if(value > data)
	{
		if(pRightTree != nullptr)
		{
			return pRightTree->Find(value);
		}
		return false;
	}
	
	if(value < data)
	{
		if(pLeftTree != nullptr)
		{
			return pLeftTree->Find(value);
		}
		return false;
	}
	return true;
}

//template <typename T>
//int BSTree<T>::BinTreeNode::GetSize(BinTreeNode* node)
//{
//	if(this == nullptr)
//	{
//		return 0;
//	}
//	else
//	{
//		return 1 + GetSize(pRightTree) + GetSize(pLeftTree);
//	}
//}

template <typename T>
T BSTree<T>::BinTreeNode::FindLargest()
{
	if(pRightTree != nullptr)
	{
		BinTreeNode* currentNode = pRightTree;
		return pRightTree->FindLargest();
	}
	return data;
}

template <typename T>
BSTree<T>::BSTree(): pRootNode(new BinTreeNode())
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
	pRootNode = rhs.pRootNode;
	return *this;
}

template<typename T>
const T& BSTree<T>::operator[](unsigned int index) const
{
	const unsigned int totalSize = Size();
	if(index >= totalSize)
	{
		throw BSTException("Value not found");
	}
	return pRootNode[index];
}

template <typename T>
void BSTree<T>::Insert(const T& value)
{
	pRootNode->Insert(value);
}

template <typename T>
void BSTree<T>::Remove(const T& value)
{
	bool didValueRemoved = pRootNode->Remove(pRootNode, nullptr, value);
	if(didValueRemoved == false)
	{
		throw BSTException("Value not found");
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
	return pRootNode->Height();
}

template <typename T>
void BSTree<T>::Clear()
{
	delete[] pRootNode;
	pRootNode = nullptr;
}

template <typename T>
bool BSTree<T>::Find(const T& value) const
{
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
	CreatePrintQueueByDepth(pRootNode, returnValue, height);
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
