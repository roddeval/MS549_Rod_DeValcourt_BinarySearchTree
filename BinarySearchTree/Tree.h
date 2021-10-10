#pragma once

#ifdef _TREE_EXPORTS
#define TREE_API __declspec(dllexport) 
#else
#define TREE_API __declspec(dllimport)  
#endif
#include <iostream>
#include <fstream>
#include <string>

struct TreeNode
{
	int data;
	TreeNode* pLeft;
	TreeNode* pRight;
	TreeNode* pParent;
};

class Tree
{
	private:
		TreeNode* mpRoot;
		int mnDebug;
		std::ofstream mFile;
		std::ofstream mFile2;
	public:
		TREE_API Tree();
		TREE_API Tree(int debug);
		TREE_API ~Tree();
		TREE_API void Initialize(int debug);
		TREE_API void DeInitialize();
		TREE_API int Add(int value);
		TREE_API int Remove(int value);
		TREE_API int Maximum();
		TREE_API int Minimum();
		TREE_API int Find(int value);
		TREE_API void InorderTraverse(int full);
		TREE_API void PreorderTraverse(int full);
		TREE_API void PostorderTraverse(int full);
		TREE_API void OutputTreeToFile(const char* path, const char* fileName, int append);
		TREE_API void OutputTreeToCSVFile(const char* path, const char* fileName, int append);
		TREE_API void OutputHorizontalTree();
	private:
		TreeNode* Add(TreeNode* pNode, int value);
		void Empty(TreeNode* pNode);
		int Successor(int value);
		int Successor(TreeNode* pNode);
		int Predecessor(int value);
		int Predecessor(TreeNode* pNode);
		TreeNode* Remove(TreeNode* pNode, int value);
		int Maximum(TreeNode* pNode);
		int Minimum(TreeNode* pNode);
		TreeNode* Find(TreeNode* pNode, int value);
		void InorderTraverse(TreeNode* pNode, int full);
		void PreorderTraverse(TreeNode* pNode, int full);
		void PostorderTraverse(TreeNode* pNode, int full);
		int EndsWith(const char* str, const char* suffix);
		void OutputTreeToFile(TreeNode* pNode);
		void OutputTreeToCSVFile(TreeNode* pNode);
		void OutputHorizontalTree(const std::string prefix,TreeNode* pNode, int isLeft);
		void OutputHorizontalTree(TreeNode* pNode);

};

