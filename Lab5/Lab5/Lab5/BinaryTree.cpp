#include "BinaryTree.h"
#include <stack>
#include <iostream>

using namespace std;

BinaryTree::BinaryTree():root(nullptr)
{}

BinaryTree::~BinaryTree()
{
	delete root;
}

void BinaryTree::make(vector<int> arr)
{
	root=makeTree(arr, 0, arr.size());
}

void BinaryTree::traversing()
{
	TLR(root, 1, 0);
	cout<<endl;
}

int BinaryTree::countNodalVerticles()
{
	int numberNodalVerticles=0;
	counter(root, numberNodalVerticles);
	return numberNodalVerticles;
}

void BinaryTree::print()
{
	printTree("", root, 0);
}

void BinaryTree::symmetricPrint()
{
	symPrintTree("", root);
}

void BinaryTree::TLR(Node*p, int level, int branch)
{
	if(p!=nullptr)
	{
		if((p->left!=nullptr)||(p->right!=nullptr))
		{
			cout<<"Nodal vertex: "<<p->data<<" level: "<<level<<" branch: ";
			if(branch==0) 
				cout<<"centre";
			else if(branch==1)
				cout<<"left";
			else cout<<"right";
			cout<<endl;
		}
		TLR(p->left, level+1, 1);
		TLR(p->right, level+1, 2);
	}
}

void BinaryTree::counter(Node* current, int &numberNodalVerticles)
{
	if(current!=nullptr)
	{
		if((current->left!=nullptr)||(current->right!=nullptr))
		numberNodalVerticles++;
		counter(current->left, numberNodalVerticles);
		counter(current->right, numberNodalVerticles);	
	}
}

Node* BinaryTree::makeTree(std::vector<int> arr, int from, int n)
{
	if(n==0) return nullptr;
	Node * p=new Node(arr[from]);
	int nl=n/2;
	int nr=n-nl-1;
	p->left=makeTree(arr, from+1, nl);
	p->right=makeTree(arr, from+1+nl, nr);
	return p;
}

void BinaryTree::printTree(const string& prefix, Node* node, bool isLeft) {
  if (node != nullptr) {
    cout << prefix;
    cout << (isLeft ? char(195) : char(192)) << char(196) << char(196);
    cout << node->data << endl;
    printTree(prefix + (isLeft ? "|   " : "    "), node->left, true);
	printTree(prefix + (isLeft ? "|   " : "    "), node->right, false);
  }
}

void BinaryTree::symPrintTree(const std::string &prefix, Node* node)
{
	if (node != nullptr) {
		string newStr;
		for(int i=0;i<prefix.size();i++)
		{
			newStr+=' ';
		}
		symPrintTree(newStr+" /", node->left);
		cout << prefix;
		//cout << (isLeft ? char(195) : char(192)) << char(196) << char(196);
		cout << node->data << endl;
		symPrintTree(newStr+" \\", node->right);
	}
}
