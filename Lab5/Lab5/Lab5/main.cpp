#include <iostream>
#include <vector>
#include "BinaryTree.h"

using namespace std;

int main()
{
    int n;
    cout<<"Enter amount of numbers: ";
    cin>>n;
    vector<int> arr(n, 0);
    for(int i=0;i<n;i++)
    {
	    int temp;
    	cin>>temp;
    	arr[i]=temp;
    }
	BinaryTree currentTree;
	currentTree.make(arr);
	cout<<"Number of nodal verticles: "<<currentTree.countNodalVerticles()<<endl;
	currentTree.traversal();
	currentTree.print();
}