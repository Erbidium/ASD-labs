#include "Node.h"

using namespace std;

Node::Node(int data):data(data), left(nullptr), right(nullptr){}

Node::~Node()
{
	delete left;
	delete right;
}

void Node::printTree()
{
	if (left != nullptr) {
    	left->printTree(false, "");
    }
	
	cout<<data<<"\n";

	if(right != nullptr) {
		right->printTree(true, "");
	}
}

void Node::printTree(bool isRight, string indent)
{
    if(left!=nullptr)
    {
        left->printTree(false, indent+(isRight?" |      ":"        "));
    }
	
    cout<<indent;
    if(isRight)
    {
    	cout<<" \\";
    }
	else
    {
		cout<<" /";
    }
    cout<<"----- "<<data<<"\n";
	
    if(right!=nullptr)
    {
        right->printTree(true, indent+(isRight?"        ":" |      "));
    }
}