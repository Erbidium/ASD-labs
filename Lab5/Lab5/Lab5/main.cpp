#include <iostream>
#include <vector>
#include "BinaryTree.h"

using namespace std;

int main()
{
    int n;
    cout<<"Enter number: ";
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
	currentTree.print();
}