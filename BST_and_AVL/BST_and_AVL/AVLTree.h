/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: AVLTree.h
Project: Assignment 4 - BST & AVL
Author: Kevin Wright
Creation date: 05/15/21
******************************************************************/
#pragma once
#include <stack>
#include <string>

#include "BSTree.h"

template <typename T>
class AVLTree : public BSTree<T>
{
public:
	AVLTree(void);

	virtual std::string GetTypeName() { return "AVLTree"; }
	virtual void Insert(const T& value);
	virtual void Remove(const T& value);

private:
	void Insert(typename BSTree<T>::BinTreeNode*& tree, const T& value, std::stack<typename BSTree<T>::BinTreeNode**>& nodes);
	void Remove(typename BSTree<T>::BinTreeNode*& tree, const T& value, std::stack<typename BSTree<T>::BinTreeNode**>& nodes);
	void Balance(std::stack<typename BSTree<T>::BinTreeNode**>& nodes);
	void RotateLeft(typename BSTree<T>::BinTreeNode*& tree);
	void RotateRight(typename BSTree<T>::BinTreeNode*& tree);
};

#include "AVLTree.hpp"
