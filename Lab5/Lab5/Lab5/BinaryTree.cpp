#include "BinaryTree.h"
#include <stack>
#include <iostream>

using namespace std;

void printBT(const std::string& prefix, const Node* node, bool isLeft);

BinaryTree::~BinaryTree()
{
	delete root;
}

void BinaryTree::buildTree(std::vector<int> arr)
{
	root=new Node(arr[0]);
	if(arr.size()>1)
	{
		int n=arr.size(), nleft=n/2, nright=n-nleft-1;
		root->left=new Node(arr[1]);
		nleft--;
		if(arr.size()>2)
		{
			root->right=new Node(arr[2]);
			nright--;
			int index=3;
			stack<Node*> leftTree, rightTree;
			leftTree.push(root->left);
			rightTree.push(root->right);
			while((nleft!=0)&&(leftTree.empty()!=true))
			{
				Node *current=leftTree.top();
				leftTree.pop();
				if(index<n)
				{
					current->left=new Node(arr[index]);
					nleft--;
					index++;
					leftTree.push(current->left);
				}
				if((index<n)&&(nleft>0))
				{
					current->right=new Node(arr[index]);
					nleft--;
					index++;
					leftTree.push(current->right);
				}

				
			}
			while((nright!=0)&&(rightTree.empty()!=true))
			{
				Node *current=rightTree.top();
				rightTree.pop();
				if(index<n)
				{
					current->left=new Node(arr[index]);
					nright--;
					index++;
					rightTree.push(current->left);
				}
				if((index<n)&&(nleft>0))
				{
					nright--;
					current->right=new Node(arr[index]);
					index++;
					rightTree.push(current->right);
				}
			}
		}
	}
}

void BinaryTree::printTree()const
{
	printBT("", root, false); 
	
}


void printBT(const std::string& prefix, const Node* node, bool isLeft)
{
    if( node != nullptr )
    {
        cout << prefix;
        cout << (isLeft ? char(195) : char(192)) << char(196) << char(196);
        cout << node->data << std::endl;
        printBT(prefix + (isLeft ? "|   " : "    "), node->left, true);
        printBT(prefix + (isLeft ? "|   " : "    "), node->right, false);
    }
}