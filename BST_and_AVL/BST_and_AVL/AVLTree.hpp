/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: AVLTree.hpp
Project: Assignment 4 - BST & AVL
Author: Sunghwan Cho
Creation date: 2/4/21
******************************************************************/

#pragma once
#include "AVLTree.h"

template <typename T>
AVLTree<T>::AVLTree()
{
}

template <typename T>
void AVLTree<T>::Insert(const T& value)
{
}

template <typename T>
void AVLTree<T>::Remove(const T& value)
{
}

template <typename T>
void AVLTree<T>::Insert(typename BSTree<T>::BinTreeNode*& tree, const T& value,
	std::stack<typename BSTree<T>::BinTreeNode**>& nodes)
{
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
}

template <typename T>
void AVLTree<T>::RotateRight(typename BSTree<T>::BinTreeNode*& tree)
{
}