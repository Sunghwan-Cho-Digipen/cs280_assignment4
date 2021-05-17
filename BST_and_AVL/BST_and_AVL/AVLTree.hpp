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
	
}

template <typename T>
void AVLTree<T>::Balance(std::stack<typename BSTree<T>::BinTreeNode**>& nodes)
{
	
}

template <typename T>
void AVLTree<T>::RotateLeft(typename BSTree<T>::BinTreeNode*& tree)
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
void AVLTree<T>::RotateRight(typename BSTree<T>::BinTreeNode*& tree)
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