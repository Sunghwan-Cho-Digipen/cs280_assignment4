/******************************************************************
CopypRightTree (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: BSTree.hpp
Project: Assignment 4 - BST & AVL
Author: Kevin Wright, Sunghwan Cho
Creation date: 2/4/21
******************************************************************/

#include <string>
#include <list>
#include <iomanip>

#include "BSTree.h"

template <typename T>
BSTree<T>::BinTreeNode::BinTreeNode(const T& value)
{
}

template <typename T>
BSTree<T>::BinTreeNode::BinTreeNode(const BinTreeNode& rhs)
{
}

template <typename T>
BSTree<T>::BinTreeNode::~BinTreeNode()
{
}

template<typename T>
inline const T& BSTree<T>::BinTreeNode::operator[](unsigned int index) const
{
	// TODO: insert return statement here
}

template <typename T>
void BSTree<T>::BinTreeNode::Insert(const T& value)
{
}

template <typename T>
bool BSTree<T>::BinTreeNode::Remove(BinTreeNode*& root, BinTreeNode* parentPtr, const T& value)
{
}

template <typename T>
int BSTree<T>::BinTreeNode::Height() const
{
}

template <typename T>
bool BSTree<T>::BinTreeNode::Find(const T& value)
{
}

template <typename T>
T BSTree<T>::BinTreeNode::FindLargest()
{
}

template <typename T>
BSTree<T>::BSTree()
{
}

template <typename T>
BSTree<T>::BSTree(const BSTree& rhs)
{
}

template <typename T>
BSTree<T>::~BSTree()
{
}

template <typename T>
BSTree<T>& BSTree<T>::operator=(const BSTree& rhs)
{
}

template<typename T>
inline const T& BSTree<T>::operator[](unsigned int index) const
{
	// TODO: insert return statement here
}

template <typename T>
void BSTree<T>::Insert(const T& value)
{
}

template <typename T>
void BSTree<T>::Remove(const T& value)
{
}

template <typename T>
bool BSTree<T>::IsEmpty() const
{
}

template <typename T>
unsigned BSTree<T>::Size() const
{
}

template <typename T>
int BSTree<T>::Height() const
{
}

template <typename T>
void BSTree<T>::Clear()
{
}

template <typename T>
bool BSTree<T>::Find(const T& value) const
{
}

template <typename T>
void BSTree<T>::ResetRoot()
{
}

template <typename T>
std::queue<typename BSTree<T>::BinTreeNode*> BSTree<T>::CreatePrintQueue() const
{
}

template <typename T>
void BSTree<T>::CreatePrintQueueByDepth(BinTreeNode* root, std::queue<BinTreeNode*>& printQueue, int depth) const
{
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
