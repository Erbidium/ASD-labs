#pragma once

struct Node
{
    int data;
    Node *left, *right;
    Node(int);
	~Node();
};
