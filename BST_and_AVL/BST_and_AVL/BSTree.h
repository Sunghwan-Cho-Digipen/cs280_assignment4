/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: BSTree.h
Project: Assignment 4 - BST & AVL
Author: Kevin Wright
Creation date: 2/4/21
******************************************************************/
#pragma once

#include <stdexcept>
#include <queue>
#include <string>

class BSTException : public std::runtime_error {
public:
	BSTException(const std::string& Message) : std::runtime_error(Message.c_str()) {};
};

template <typename T>
class BSTree {
protected:
	class BinTreeNode {
	public:
		BinTreeNode(const T& value);			
		BinTreeNode(const BinTreeNode& rhs);
		BinTreeNode(BinTreeNode&& rhs) = delete;
		~BinTreeNode();

		BinTreeNode& operator =(BinTreeNode& rhs) = delete;
		const T& operator[](unsigned int index) const;

		void Insert(const T& value);
		bool Remove(BinTreeNode*& root, BinTreeNode* parentPtr, const T& value);
		int Height() const;
		bool Find(const T& value);
		T FindLargest();

		BinTreeNode* pLeftTree;
		BinTreeNode* pRightTree;
		T data;
		unsigned int size;
	};
public:
	BSTree();					// Basic constructor for the BST
	BSTree(const BSTree& rhs);	// Copy Constructor doing a deep copy
	virtual ~BSTree();			// Descturctor using ~BinTreeNode

	BSTree& operator=(const BSTree& rhs);	//Assignment operator doing shallow copy
	const T& operator[](unsigned int index) const;	//uses BinTreeNode operator[]

	virtual std::string GetTypeName() { return "BSTree"; }
	virtual void Insert(const T& value);
	virtual void Remove(const T& value);

	bool IsEmpty() const;
	unsigned int Size() const;
	int Height() const;
	void Clear();
	bool Find(const T& value) const;
	void ResetRoot();

	void DebugPrint(bool showCounts = false) const;

protected:
	BinTreeNode* pRootNode;
private:
	std::queue<BinTreeNode*> CreatePrintQueue() const;
	void CreatePrintQueueByDepth(BinTreeNode* root, std::queue<BinTreeNode*>& printQueue, int depth) const;
};

#include "BSTree.hpp"