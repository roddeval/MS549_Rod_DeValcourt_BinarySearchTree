#include "pch.h"
#include "Tree.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

Tree::Tree()
{
	cout << "Tree::Tree" << endl;
	Initialize(1);
}

Tree::Tree(int debug)
{
	if (debug == 1)
		cout << "Tree::Tree(" << debug << ")" << endl;
	Initialize(debug);
	mnDebug = debug;
}

Tree::~Tree()
{
	if (mnDebug == 1)
		cout << "Tree::~Tree" << endl;
	DeInitialize();
}

void Tree::Initialize(int debug)
{
	if (debug == 1)
		cout << "Tree::Initialize" << endl;
	mpRoot = NULL;
	mnDebug = debug;
}

void Tree::DeInitialize()
{
	if (mnDebug == 1)
		cout << "Tree::DeInitialize" << endl;
	if (mpRoot != NULL)
	{
		Empty(mpRoot);
	}
}

int Tree::Add(int value)
{
	if (mnDebug == 1)
		cout << "Tree::Add(int " << value << " )" << endl;

	int result = Find(value);

	if (result == 0)
	{
		mpRoot = Add(mpRoot, value);
	}
	return result;
}

int Tree::Remove(int value)
{
	if (mnDebug == 1)
		cout << "Tree::Remove(int " << value << " )" << endl;

	int result = Find(value);
	if (result == 1)
	{
		Remove(mpRoot, value);
	}
	return result;
}

int Tree::Maximum()
{
	if (mnDebug == 1)
		cout << "Tree::Maximum" << endl;
	int result = -1;
	result = Maximum(mpRoot);
	return result;
}

int Tree::Minimum()
{
	if (mnDebug == 1)
		cout << "Tree::Minimum" << endl;
	int result = -1;
	result = Minimum(mpRoot);
	return result;
}

int Tree::Find(int value)
{
	if (mnDebug == 1)
		cout << "Tree::Find(value " << value << " )" << endl;
	int result = -1;
	TreeNode* pFoundNode = NULL;
	pFoundNode = Find(mpRoot, value);
	if (pFoundNode != NULL)
	{
		result = (value == pFoundNode->data) ? 1 : 0;
	}
	else
	{
		result = 0;
	}
	return result;
}

void Tree::InorderTraverse(int full)
{
	if (mnDebug == 1)
		cout << "Tree::InorderTraverse" << endl;
	cout << "root :" << mpRoot << endl;
	InorderTraverse(mpRoot,full);
	if (full == 0)
		cout << endl;
}

void Tree::PreorderTraverse(int full)
{
	if (mnDebug == 1)
		cout << "Tree::PreorderTraverse" << endl;
	cout << "root :" << mpRoot << endl;
	PreorderTraverse(mpRoot,full);
	if (full == 0)
		cout << endl;
}
void Tree::PostorderTraverse(int full)
{
	if (mnDebug == 1)
		cout << "Tree::PostorderTraverse" << endl;
	cout << "root :" << mpRoot << endl;
	PostorderTraverse(mpRoot,full);
	if (full == 0)
		cout << endl;
}

void Tree::OutputTreeToFile(const char* path, const char* fileName, int append)
{
	string pathPlusFile = "";

	pathPlusFile = path;

	const char* c = pathPlusFile.c_str();
	const char* ending = "\\";

	if (EndsWith(c, ending) == 0)
	{
		pathPlusFile = pathPlusFile + "\\";
	}
	pathPlusFile = pathPlusFile + fileName;

	if (append == 0)
		mFile.open(pathPlusFile, ios::out | ios::trunc);
	else
		mFile.open(pathPlusFile, ios::out);

	OutputTreeToFile(mpRoot);

	mFile.flush();
	mFile.close();

}

void Tree::OutputTreeToCSVFile(const char* path, const char* fileName, int append)
{
	string pathPlusFile = "";

	pathPlusFile = path;

	const char* c = pathPlusFile.c_str();
	const char* ending = "\\";

	if (EndsWith(c, ending) == 0)
	{
		pathPlusFile = pathPlusFile + "\\";
	}
	pathPlusFile = pathPlusFile + fileName;

	if (append == 0)
		mFile.open(pathPlusFile, ios::out | ios::trunc);
	else
		mFile.open(pathPlusFile, ios::out);

	mFile << "NODE,DATA,PARENT,LEFT,RIGHT" << char(13) << char(10);

	OutputTreeToCSVFile(mpRoot);

	mFile.flush();
	mFile.close();



}

void Tree::OutputHorizontalTree()
{
	OutputHorizontalTree(mpRoot);
}


TreeNode* Tree::Add(TreeNode* pNode, int value)
{
	if (mnDebug == 1)
		cout << "Tree::Add(TreeNode* " << pNode << ", int " << value << " )" << endl;
	if (pNode == NULL)
	{
		pNode = new TreeNode();
		pNode->data = value;
		pNode->pLeft = NULL;
		pNode->pRight = NULL;
		pNode->pParent = NULL;
	}
	else
	{
		if (pNode->data < value)
		{
			pNode->pRight = Add(pNode->pRight, value);
			pNode->pRight->pParent = pNode;
		}
		else
		{
			pNode->pLeft = Add(pNode->pLeft, value);
			pNode->pLeft->pParent = pNode;

		}
	}
	return pNode;
}

void Tree::Empty(TreeNode* pNode)
{
	// remove here is a postorder traversal for obvious reasons
	if (mnDebug == 1)
		cout << "Tree::Empty(TreeNode* " << pNode << " )" << endl;
	if (pNode != NULL)
	{
		Empty(pNode->pLeft);
		Empty(pNode->pRight);
		delete pNode;
	}
}

int Tree::Successor(int value)
{
	if (mnDebug == 1)
		cout << "Tree::Successor(key " << value << " )" << endl;
	TreeNode* keyNode = Find(mpRoot, value);
	return (keyNode == NULL) ? -1 : Successor(keyNode);
}

int Tree::Successor(TreeNode* pNode)
{
	if (mnDebug == 1)
		cout << "Tree::Successor(TreeNode* " << pNode << " )" << endl;
	if (pNode != NULL)
	{
		if (pNode->pRight != NULL)
		{
			return Minimum(pNode->pRight);
		}
		else
		{
			TreeNode* parentNode = pNode->pParent;
			TreeNode* currentNode = pNode;
			while ((parentNode != NULL) && (currentNode == parentNode->pRight))
			{
				currentNode = parentNode;
				parentNode = currentNode->pParent;
			}
			return (parentNode == NULL) ? -1 : parentNode->data;
		}
	}
	return -1;
}

int Tree::Predecessor(int value)
{
	if (mnDebug == 1)
		cout << "Tree::Predecessor(value " << value << " )" << endl;
	TreeNode* pNode = Find(mpRoot, value);
	return (pNode == NULL) ? -1 : Predecessor(pNode);
}

int Tree::Predecessor(TreeNode* pNode)
{
	if (mnDebug == 1)
		cout << "Tree::Predecessor(TreeNode* " << pNode << " )" << endl;
	if (pNode->pLeft != NULL)
	{
		return Maximum(pNode->pLeft);
	}
	else
	{
		TreeNode* pParent = pNode->pParent;
		TreeNode* pCurrent = pNode;
		while ((pParent != NULL) && (pCurrent == pParent->pLeft))
		{
			pCurrent = pParent;
			pParent = pCurrent->pParent;
		}
		return pParent == NULL ? -1 : pParent->data;
	}
}

TreeNode* Tree::Remove(TreeNode* pNode, int value)
{
	if (mnDebug == 1)
		cout << "Tree::Remove(TreeNode* " << pNode << ", value " << value << " )" << endl;
	int data = 0;
	if (pNode == NULL)
	{
		return NULL;
	}
	else
	{
		if (pNode->data == value)
		{
			if (mnDebug == 1)
			{
				cout << pNode->data << " == " << value << endl;
				cout << "Removing pNode: " << pNode << endl;
			}

			if ((pNode->pLeft == NULL) && (pNode->pRight == NULL))
			{
				pNode = NULL;
			}
			else
			{
				if ((pNode->pLeft == NULL) && (pNode->pRight != NULL))
				{
					pNode->pRight->pParent = pNode->pParent;
					pNode = pNode->pRight;
				}
				else
				{
					if ((pNode->pLeft != NULL) && (pNode->pRight == NULL))
					{
						pNode->pLeft->pParent = pNode->pParent;
						pNode = pNode->pLeft;
					}
					else
					{
						data = Successor(value);
						pNode->data = data;
						pNode->pRight = Remove(pNode->pRight, data);
					}
				}

			}
		}
		else
		{
			if (pNode->data < value)
			{
				pNode->pRight = Remove(pNode->pRight, value);
			}
			else
			{
				pNode->pLeft = Remove(pNode->pLeft, value);
			}
		}
	}
	return pNode;
}

int Tree::Maximum(TreeNode* pNode)
{
	if (mnDebug == 1)
		cout << "Tree::Maximum(TreeNode* " << pNode << " )" << endl;
	if (pNode == NULL)
	{
		return -1;
	}
	else
	{
		if (pNode->pRight == NULL)
		{
			return pNode->data;
		}
		else
		{
			return Maximum(pNode->pRight);
		}
	}
}

int Tree::Minimum(TreeNode* pNode)
{
	if (mnDebug == 1)
		cout << "Tree::Minimum(TreeNode* " << pNode << " )" << endl;
	if (pNode == NULL)
	{
		return -1;
	}
	else
	{
		if (pNode->pLeft == NULL)
		{
			return pNode->data;
		}
		else
		{
			return Minimum(pNode->pLeft);
		}
	}
}

TreeNode* Tree::Find(TreeNode* pNode, int value)
{
	if (mnDebug == 1)
		cout << "Tree::Find(TreeNode* " << pNode << ", value " << value << " )" << endl;
	if (pNode == NULL)
	{
		return NULL;
	}
	else
	{
		if (pNode->data == value)
		{
			return pNode;
		}
		else
		{
			if (pNode->data < value)
			{
				return Find(pNode->pRight, value);
			}
			else
			{
				return Find(pNode->pLeft, value);
			}
		}
	}
}

void Tree::InorderTraverse(TreeNode* pNode, int full)
{
	if (mnDebug == 1)
		cout << "Tree::InorderTraverse(TreeNode* " << pNode << " )" << endl;

	if (pNode != NULL)
	{
		InorderTraverse(pNode->pLeft,full);

		if (full == 1)
		{
			cout << "         pNode: " << pNode << endl;
			cout << "   pNode->data: " << pNode->data << endl;
			cout << "pNode->pParent: " << pNode->pParent << endl;
			cout << "  pNode->pLeft: " << pNode->pLeft << endl;
			cout << " pNode->pRight: " << pNode->pRight << endl;
			cout << "---------------" << endl;
		}
		else
		{
			cout << pNode->data << " ";
		}
		InorderTraverse(pNode->pRight,full);
	}
}

void Tree::PreorderTraverse(TreeNode* pNode, int full)
{
	if (mnDebug == 1)
		cout << "Tree::PreorderTraverse(TreeNode* " << pNode << " )" << endl;

	if (pNode != NULL)
	{
		if (full == 1)
		{
			cout << "         pNode: " << pNode << endl;
			cout << "   pNode->data: " << pNode->data << endl;
			cout << "pNode->pParent: " << pNode->pParent << endl;
			cout << "  pNode->pLeft: " << pNode->pLeft << endl;
			cout << " pNode->pRight: " << pNode->pRight << endl;
			cout << "---------------" << endl;
		}
		else
		{
			cout << pNode->data << " ";
		}
		PreorderTraverse(pNode->pLeft, full);
		PreorderTraverse(pNode->pRight, full);
	}
}
void Tree::PostorderTraverse(TreeNode* pNode, int full)
{
	if (mnDebug == 1)
		cout << "Tree::PostorderTraverse(TreeNode* " << pNode << " )" << endl;

	if (pNode != NULL)
	{
		PostorderTraverse(pNode->pLeft, full);
		PostorderTraverse(pNode->pRight, full);
		if (full == 1)
		{
			cout << "         pNode: " << pNode << endl;
			cout << "   pNode->data: " << pNode->data << endl;
			cout << "pNode->pParent: " << pNode->pParent << endl;
			cout << "  pNode->pLeft: " << pNode->pLeft << endl;
			cout << " pNode->pRight: " << pNode->pRight << endl;
			cout << "---------------" << endl;
		}
		else
		{
			cout << pNode->data << " ";
		}
	}
}

int Tree::EndsWith(const char* str, const char* suffix)
{
	if ((str == NULL) || (suffix == NULL))
	{
		return 0;
	}
	size_t str_len = strlen(str);
	size_t suffix_len = strlen(suffix);

	if (suffix_len > str_len)
	{
		return 0;
	}

	return 0 == strncmp(str + str_len - suffix_len, suffix, suffix_len);

}

void Tree::OutputTreeToFile(TreeNode* pNode)
{
	if (mnDebug == 1)
		cout << "Tree::OutputTreeToFile(TreeNode* " << pNode << " )" << endl;

	if (pNode == NULL)
	{
		return;
	}
	OutputTreeToFile(pNode->pLeft);
	mFile << "         pNode: " << pNode << char(13) << char(10);
	mFile << "   pNode->data: " << pNode->data << char(13) << char(10);
	mFile << "pNode->pParent: " << pNode->pParent << char(13) << char(10);
	mFile << "  pNode->pLeft: " << pNode->pLeft << char(13) << char(10);
	mFile << " pNode->pRight: " << pNode->pRight << char(13) << char(10);
	mFile << "---------------" << char(13) << char(10);

	OutputTreeToFile(pNode->pRight);

}

void Tree::OutputTreeToCSVFile(TreeNode* pNode)
{
	if (mnDebug == 1)
		cout << "Tree::OutputTreeToFile(TreeNode* " << pNode << " )" << endl;

	if (pNode == NULL)
	{
		return;
	}

	mFile << pNode << "," << pNode->data << "," << pNode->pParent << "," << pNode->pLeft << "," << pNode->pRight << char(13) << char(10);
	OutputTreeToCSVFile(pNode->pLeft);
	OutputTreeToCSVFile(pNode->pRight);
}

void Tree::OutputHorizontalTree(const std::string prefix, TreeNode* pNode, int isLeft)
{
	if (pNode != NULL)
	{
		cout << prefix;
		cout << (isLeft ? "|--" : "t--");
		cout << pNode->data << endl;

		OutputHorizontalTree(prefix + (isLeft ? "|   " : "    "), pNode->pLeft, true);

		OutputHorizontalTree(prefix + (isLeft ? "|   " : "    "), pNode->pRight, false);

	}
}

void Tree::OutputHorizontalTree(TreeNode* pNode)
{
	OutputHorizontalTree("", pNode, false);
}