/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: Main.cpp
Project: Assignment 4 - BST & AVL
Author: Kevin Wright
Creation date: 2/4/21
******************************************************************/
#include <iostream>


#include <random>
#include <set>

#include "BSTree.h"
#include "AVLTree.h"

#include <crtdbg.h>
#if _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define malloc(s) _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif

void GetRandomValues(int* array, int size) {
	std::mt19937 rand(2);	// Hard coded to this because the numbers looked good
	std::uniform_int_distribution<> dist(0, 9);
	std::set<int> set;
	for (int i = 0; i < size;) {
		int val = dist(rand);
		if (set.find(val) == set.end()) {
			set.insert(val);
			array[i++] = val;
		}
	}
}

template <typename T>
void Test1(void) {
	T tree;
	const int size = 10;
	int values[size];
	GetRandomValues(values, size);

	std::cout << "====================== Test1 - random insert  ======================\n";
	std::cout << tree.GetTypeName() << std::endl;

	for (int i = 0; i < size; i++) {
		tree.Insert(values[i]);
		tree.DebugPrint();
	}
}


template <typename T>
void Test2(void) {
	T tree;
	const int size = 7;

	std::cout << "====================== Test2 - sorted insert  ======================\n";
	std::cout << tree.GetTypeName() << std::endl;

	for (int i = 0; i < size; i++) {
		tree.Insert(i);
	}
	tree.DebugPrint();
}

template <typename T>
void Test3(void) {
	T tree;
	const int size = 10;
	int values[size];
	GetRandomValues(values, size);

	std::cout << "====================== Test3 - random insert/remove ======================\n";
	std::cout << tree.GetTypeName() << std::endl;

	for (int i = 0; i < size; i++) {
		tree.Insert(values[i]);
	}
	tree.DebugPrint(true);

	std::cout << "remove 7, 8, 2, 9" << std::endl << std::endl;
	tree.Remove(7);
	tree.DebugPrint(true);
	tree.Remove(8);
	tree.DebugPrint(true);
	tree.Remove(2);
	tree.DebugPrint(true);
	tree.Remove(9);
	tree.DebugPrint(true);
}

template <typename T>
void Test4(void) {
	T tree;
	const int size = 10;
	int values[size];
	GetRandomValues(values, size);

	std::cout << "====================== Test4 - random insert/remove all ======================\n";
	std::cout << tree.GetTypeName() << std::endl;

	for (int i = 0; i < size; i++) {
		tree.Insert(values[i]);
	}
	tree.DebugPrint(true);

	std::cout << "remove 2, 0, 1, 4, 3:" << std::endl << std::endl;
	tree.Remove(2);
	tree.DebugPrint(true);
	tree.Remove(0);
	tree.DebugPrint(true);
	tree.Remove(1);
	tree.DebugPrint(true);
	tree.Remove(4);
	tree.DebugPrint(true);
	tree.Remove(3);
	tree.DebugPrint(true);

	std::cout << "remove some invalid (10, -1):" << std::endl << std::endl;
	try {
		tree.Remove(10);
	} catch (const BSTException& exception) {
		std::cout << exception.what() << std::endl;
	}

	try {
		tree.Remove(-1);
	} catch (const BSTException& exception) {
		std::cout << exception.what() << std::endl;
	}
	tree.DebugPrint(true);

	std::cout << "remove 6, 5, 8, 9, 7:" << std::endl << std::endl;
	tree.Remove(6);
	tree.DebugPrint(true);
	tree.Remove(5);
	tree.DebugPrint(true);
	tree.Remove(8);
	tree.DebugPrint(true);
	tree.Remove(9);
	tree.DebugPrint(true);
	tree.Remove(7);
	tree.DebugPrint(true);

	std::cout << "remove 2 from IsEmpty tree:" << std::endl;
	try {
		tree.Remove(2);
	} catch (const BSTException& exception) {
		std::cout << exception.what() << std::endl;
	}
	tree.DebugPrint();
}

template <typename T>
void Test5(void) {
	T tree;
	const int size = 10;
	int values[size];
	GetRandomValues(values, size);

	std::cout << "====================== Test5 - random insert/clear/insert ======================\n";
	std::cout << tree.GetTypeName() << std::endl;

	for (int i = 0; i < size; i++) {
		tree.Insert(values[i]);
	}
	tree.DebugPrint();

	std::cout << std::endl << "clear:" << std::endl;
	tree.Clear();
	tree.DebugPrint();
	if (tree.IsEmpty() == true) {
		std::cout << "Tree is IsEmpty";
	} else {
		std::cout << "Tree is NOT IsEmpty";
	}

	std::cout << std::endl << "Insert:" << std::endl;
	for (int i = 0; i < size; i++) {
		tree.Insert(values[i]);
	}
	tree.DebugPrint();
	if (tree.IsEmpty() == true) {
		std::cout << "Tree is IsEmpty";
	} else {
		std::cout << "Tree is NOT IsEmpty";
	}
}

template <typename T>
void Test6(void) {
	T tree;
	const int size = 10;
	int values[size];
	GetRandomValues(values, size);

	std::cout << "====================== Test6 - random insert/find ======================\n";
	std::cout << tree.GetTypeName() << std::endl;

	for (int i = 0; i < size; i++) {
		tree.Insert(values[i]);
	}

	tree.DebugPrint();
	int value;

	value = 1;
	std::cout << "Value " << value << (tree.Find(value) ? " found" : " NOT found") << std::endl;
	value = 3;
	std::cout << "Value " << value << (tree.Find(value) ? " found" : " NOT found") << std::endl;
	value = 5;
	std::cout << "Value " << value << (tree.Find(value) ? " found" : " NOT found") << std::endl;
	value = 50;
	std::cout << "Value " << value << (tree.Find(value) ? " found" : " NOT found") << std::endl;
}

template <typename T>
void Test7(void) {
	T tree1, tree2;
	const int size = 10;
	int values[size];
	GetRandomValues(values, size);

	std::cout << "====================== Test7 - assignment ======================\n";
	std::cout << tree1.GetTypeName() << std::endl;

	for (int i = 0; i < size; i++) {
		tree1.Insert(values[i]);
		tree2.Insert(values[i] * 3);
	}
	std::cout << "tree 1 ------------------------------------------\n";
	tree1.DebugPrint();

	std::cout << "tree 2 ------------------------------------------\n";
	tree2.DebugPrint();

	tree1 = tree2;

	std::cout << "Remove 21 from tree 1\n";
	tree1.Remove(21);
	std::cout << "tree 1 ------------------------------------------\n";
	tree1.DebugPrint();
	std::cout << "tree 2 ------------------------------------------\n";
	tree2.DebugPrint();

	// The 2 trees point to the same data, which can cause a major issue (problem with shallow copy)
	// When 1 tree is deleted that means the second is a dangling pointer (bad)
	// The ResetRoot is a hack to avoid a crash.  Do something to the second tree to prevent the crash.
	tree2.ResetRoot();	
}

template <typename T>
void Test8(void) {
	T tree1;
	const int size = 10;
	int values[size];
	GetRandomValues(values, size);

	std::cout << "====================== Test8 - copy constructor ======================\n";
	std::cout << tree1.GetTypeName() << std::endl;

	for (int i = 0; i < size; i++) {
		tree1.Insert(values[i]);
	}
	std::cout << "tree 1 ------------------------------------------\n";
	tree1.DebugPrint();

	std::cout << "tree 2 ------------------------------------------\n";
	T tree2(tree1);
	tree1.DebugPrint();

	std::cout << "Remove 7 from tree 1\n";
	tree1.Remove(7);
	std::cout << "tree 1 ------------------------------------------\n";
	tree1.DebugPrint();
	std::cout << "tree 2 ------------------------------------------\n";
	tree2.DebugPrint();
}

template <typename T>
void TestIndex(void) {
	T tree;
	std::string randomLetters = "ASERCHIN";

	std::cout << "====================== TestIndex - random insert/subscript ======================\n";
	std::cout << tree.GetTypeName() << std::endl;

	for (unsigned int i = 0; i < randomLetters.length(); i++) {
		tree.Insert(randomLetters[i]);
	}
	tree.DebugPrint();

	for (unsigned int i = 0; i < randomLetters.length(); i++) {
		std::cout << "Index " << i << ": " << tree[i] << std::endl;
	}
	try {
		std::cout << "Index " << randomLetters.length() << ": ";
		std::cout << tree[randomLetters.length()] << std::endl;
	} catch (const BSTException& exception) {
		std::cout << exception.what() << std::endl;
	}
}

void AVLStress(void) {
	std::cout << "====================== AVLStress ======================\n";

	int* ia = 0;

	AVLTree<int> tree;

	int size = 10000;

	ia = new int[size];
	for (int i = 0; i < size; i++)
		ia[i] = i;

	for (int i = 0; i < size; i++) {
		tree.Insert(ia[i]);
	}

	// Stress indexing
	int sum = 0;
	for (int j = 0; j < 1000; j++)
		for (int i = size - 1; i > size - 1000; i--)
			sum += tree[i];
	std::cout << "Sum is " << sum << std::endl;
	std::cout << "Remove stuff" << std::endl;

	for (int i = 0; i < size - 10; i++) {
		tree.Remove(ia[i]);
	}

	tree.DebugPrint();
	for (unsigned i = 0; i < tree.Size(); i++) {
		std::cout << "Index " << i << ": " << tree[static_cast<int>(i)] << std::endl;
	}

	delete[] ia;
}

#include <string>
template <typename T>
void TestStrings(void) {
	const char* test = "TestStrings";
	std::cout << "====================== " << test << " ======================\n";

	try {
		T tree;
		std::cout << tree.GetTypeName() << std::endl;

		const char* strs[] = { "abe", "for", "fad", "one", "two", "six", "box",
							  "zoo", "car", "dog", "dig", "fat", "fav", "hit",
							  "cab", "abd", "sox", "man", "boy", "sow", "abc",
		};

		size_t size = sizeof(strs) / sizeof(*strs);
		for (size_t i = 0; i < size; i++)
			tree.Insert(strs[i]);

		tree.DebugPrint();

		std::string value = "dig";
		std::cout << "Value " << value << (tree.Find(value) ? " found" : " NOT found") << std::endl;
		value = "abe";
		std::cout << "Value " << value << (tree.Find(value) ? " found" : " NOT found") << std::endl;
		value = "hot";
		std::cout << "Value " << value << (tree.Find(value) ? " found" : " NOT found") << std::endl;
		value = "abcd";
		std::cout << "Value " << value << (tree.Find(value) ? " found" : " NOT found") << std::endl;

		for (size_t i = 0; i < size; i++)
			std::cout << "Index " << i << ": " << tree[static_cast<int>(i)] << std::endl;
	} catch (const BSTException& e) {
		std::cout << "BSTException: " << e.what() << std::endl;
	} catch (...) {
		std::cout << "Unknown exception." << std::endl;
	}
}

//***********************************************************************
//***********************************************************************
//***********************************************************************

int main() {
	int test_num = -1;
#ifndef _MSC_VER
	std::cin >> test_num;
#endif

	void(*tests[])() = {
		Test1<BSTree<int> >,				//  1 random insert
		Test2<BSTree<int> >,				//  2 sorted insert
		Test3<BSTree<int> >,				//  3 random insert/remove some
		Test4<BSTree<int> >,				//  4 random insert/remove all
		Test5<BSTree<int> >,				//  5 random insert/clear
		Test6<BSTree<int> >,				//  6 random insert/find
		Test7<BSTree<int> >,				//  7 assignment
		Test8<BSTree<int> >,				//  8 copy constructor

		//Test1<AVLTree<int> >,				//  9 random insert
		//Test2<AVLTree<int> >,				// 10 sorted insert
		//Test3<AVLTree<int> >,				// 11 random insert/remove some
		//Test4<AVLTree<int> >,				// 12 random insert/remove all
		//Test5<AVLTree<int> >,				// 13 random insert/clear
		//Test6<AVLTree<int> >,				// 14 random insert/find
		//Test7<AVLTree<int> >,				// 15 assignment
		//Test8<AVLTree<int> >,				// 16 copy constructor

		TestIndex<BSTree<char> >,			// 17 random insert/select
		//TestIndex<AVLTree<char> >,			// 18 random insert/select
		TestStrings<BSTree<std::string> >,	// 19 random insert strings/select
		//TestStrings<AVLTree<std::string> >,	// 20 random insert strings/select/
		//AVLStress,							// 21 stress avl only
	};
	int numTests = static_cast<int>(sizeof(tests) / sizeof(*tests));
	if (test_num > 0) {
		try {
			tests[test_num - 1]();
		} catch (const BSTException& e) {
			std::cout << "BSTException: " << e.what() << std::endl;
		} catch (...) {
			std::cout << "unknown exception" << std::endl;
		}
	} else {
		for (int i = 0; i < numTests; i++) {
			try {
				tests[i]();
			} catch (const BSTException& e) {
				std::cout << "BSTException: " << e.what() << std::endl;
			} catch (...) {
				std::cout << "unknown exception" << std::endl;
			}
			std::cout << std::endl << std::endl;
		}
	}

#ifdef _MSC_VER
	system("pause");
#endif

	_CrtDumpMemoryLeaks();
	return 0;
}
