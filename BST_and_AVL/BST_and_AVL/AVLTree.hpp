/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: AVLTree.hpp
Project: Assignment 4 - BST & AVL
Author: Sunghwan Cho
Creation date: 05/15/21
******************************************************************/

#pragma once
#include "AVLTree.h"

template <typename T>
AVLTree<T>::AVLTree()
	:BSTree<T>()
{
	
}

template <typename T>
void AVLTree<T>::Insert(const T& value)
{
	std::stack<typename BSTree<T>::BinTreeNode**> nodeStack;
	Insert(this->pRootNode, value, nodeStack);
	Balance(nodeStack);
}

template <typename T>
void AVLTree<T>::Remove(const T& value)
{
	if (this->pRootNode == nullptr)
	{
		throw BSTException("Item was not found");
	}
	if (this->pRootNode->Find(value) == false)
	{
		throw BSTException("Item was not found");
	}

	std::stack<typename BSTree<T>::BinTreeNode**> nodeStack;
	Remove(this->pRootNode, value, nodeStack);
	Balance(nodeStack);
}

template <typename T>
void AVLTree<T>::Insert(typename BSTree<T>::BinTreeNode*& tree, const T& value,
	std::stack<typename BSTree<T>::BinTreeNode**>& nodes)
{
	if (tree == nullptr)
	{
		tree = new typename BSTree<T>::BinTreeNode(value);
		nodes.push(&tree);
		return;
	}

	nodes.push(&tree);

	++tree->size;

	if (tree->data <= value)
	{
		if (tree->pRightTree == nullptr)
		{
			tree->pRightTree = new typename BSTree<T>::BinTreeNode(value);
		}
		else
		{
			Insert(tree->pRightTree, value, nodes);
		}

		return;
	}

	if (tree->pLeftTree == nullptr)
	{
		tree->pLeftTree = new typename BSTree<T>::BinTreeNode(value);
	}
	else
	{
		Insert(tree->pLeftTree, value, nodes);
	}
}

template <typename T>
void AVLTree<T>::Remove(typename BSTree<T>::BinTreeNode*& tree, const T& value,
	std::stack<typename BSTree<T>::BinTreeNode**>& nodes)
{
	if (tree == nullptr)
	{
		throw BSTException("Item was not found");
	}

	if (tree->data < value)
	{
		if (tree->pRightTree == nullptr)
		{
			throw BSTException("Item was not found");
		}
		
		--tree->size;
		nodes.push(&tree);
		Remove(tree->pRightTree, value, nodes);
		return;
	}

	if (tree->data > value)
	{
		if (tree->pLeftTree == nullptr)
		{
			throw BSTException("Item was not found");
		}
		
		--tree->size;
		nodes.push(&tree);
		Remove(tree->pLeftTree, value, nodes);
		return;
	}
	
	typename BSTree<T>::BinTreeNode** topPointer = nullptr;
	if (this->pRootNode != tree)
	{
		topPointer = nodes.top();
	}
	
	if (tree->pLeftTree != nullptr && tree->pRightTree != nullptr)
	{
		tree->data = tree->pLeftTree->FindLargest();
		--tree->size;
		nodes.push(&tree);
		Remove(tree->pLeftTree, tree->data, nodes);
	}
	else if (tree->pLeftTree == nullptr || tree->pRightTree == nullptr)
	{
		typename BSTree<T>::BinTreeNode* childPtr = (tree->pLeftTree == nullptr ? tree->pRightTree : tree->pLeftTree);
		typename BSTree<T>::BinTreeNode* currentPtr = tree;
		currentPtr->pLeftTree = currentPtr->pRightTree = nullptr;

		if (topPointer == nullptr)
		{
			this->pRootNode = childPtr;
			delete currentPtr;
			return;
		}

		typename BSTree<T>::BinTreeNode*& childTreePointer = (*topPointer)->pLeftTree == tree ? (*topPointer)->pLeftTree : (*topPointer)->pRightTree;

		--currentPtr->size;
		delete currentPtr;
		childTreePointer = childPtr;
	}
	else if (tree->pLeftTree == nullptr && tree->pRightTree == nullptr)
	{
		if (topPointer == nullptr)
		{
			delete tree;
			this->pRootNode = nullptr;
			return;
		}
		
		typename BSTree<T>::BinTreeNode*& childTreePointer = (*topPointer)->pLeftTree == tree ? (*topPointer)->pLeftTree : (*topPointer)->pRightTree;
		
		--tree->size;
		delete tree;
		childTreePointer = nullptr;
	}
}

template <typename T>
void AVLTree<T>::Balance(std::stack<typename BSTree<T>::BinTreeNode**>& nodes)
{
	if (nodes.empty() == true)
	{
		return;
	}

	while (nodes.empty() == false)
	{
		typename BSTree<T>::BinTreeNode** node_ptr = nodes.top();
		nodes.pop();
		const int Subtraction = Subtract(*node_ptr);
		
		if (Subtraction > 1)
		{
			typename BSTree<T>::BinTreeNode* child = (*node_ptr)->pLeftTree;
			const int ChildSubtraction = Subtract(child);
			
			if (ChildSubtraction >= 0)
			{
				RotateRight(*node_ptr); // This should be LL rotation so RotateRight()
			}
			else
			{
				RotateLeft((*node_ptr)->pLeftTree); // This should be LR rotation so RotateLeft() and Rotate Right()
				RotateRight(*node_ptr);
			}
			return;
		}

		if (Subtraction < -1)
		{
			typename BSTree<T>::BinTreeNode* child = (*node_ptr)->pRightTree;
			const int ChildSubtraction = Subtract(child);
			
			if (ChildSubtraction <= 0)
			{
				RotateLeft(*node_ptr); // This should be RR rotation so RotateLeft()
			}
			else
			{
				RotateRight((*node_ptr)->pRightTree); // This should be RL rotation so RotateRight() and RotateLeft()
				RotateLeft(*node_ptr);
			}
			return;
		}
	}
}

template <typename T>
void AVLTree<T>::RotateLeft(typename BSTree<T>::BinTreeNode*& tree) // Rotate "to" left
{	
	typename BSTree<T>::BinTreeNode* parent = tree;
	typename BSTree<T>::BinTreeNode* child = tree->pRightTree;

	const int ParentSize = parent->size;
	const int ChildSize = child->size;
	const int SizeOfLeftChildOfChild = (child->pLeftTree == nullptr) ? 0 : child->pLeftTree->size;

	parent->pRightTree = child->pLeftTree;
	child->pLeftTree = parent;

	tree = child;
	tree->pLeftTree->size = ParentSize - ChildSize + SizeOfLeftChildOfChild;
	tree->size = ChildSize - SizeOfLeftChildOfChild + tree->pLeftTree->size;
}

template <typename T>
void AVLTree<T>::RotateRight(typename BSTree<T>::BinTreeNode*& tree) // Rotate "to" right
{	
	typename BSTree<T>::BinTreeNode* parent = tree;
	typename BSTree<T>::BinTreeNode* child = tree->pLeftTree;

	const int ParentSize = parent->size;
	const int ChildSize = child->size;
	const int SizeOfRightChildOfChild = (child->pRightTree == nullptr) ? 0 : child->pRightTree->size;

	parent->pLeftTree = child->pRightTree;
	child->pRightTree = parent;

	tree = child;
	tree->pRightTree->size = ParentSize - ChildSize + SizeOfRightChildOfChild;
	tree->size = ChildSize - SizeOfRightChildOfChild + tree->pRightTree->size;
}

template <typename T>
int AVLTree<T>::Subtract(typename BSTree<T>::BinTreeNode* node)
{
	const int LeftTreeHeight = node->pLeftTree != nullptr ? (node)->pLeftTree->Height() : -1;
	const int RightTreeHeight = node->pRightTree != nullptr ? (node)->pRightTree->Height() : -1;
	return LeftTreeHeight - RightTreeHeight;
}

