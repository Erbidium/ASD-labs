#include <iostream>
#include <vector>
#include <stack>
#include <ctime>

using namespace std;

struct verticleState
{
	bool isVisited;
	int previous;
};

void DFS(vector<vector<int>>& adjacencyMatrix);
void fillAdjacencyMatrix(vector<vector<int>>& adjacencyMatrix);
void printStack(stack<int> unprocessedVerticles);
void printMatrix(const vector<vector<int>>& matrix);

int main()
{
	srand(time(NULL));
	vector<vector<int>> adjacencyMatrix;
	fillAdjacencyMatrix(adjacencyMatrix);
	DFS(adjacencyMatrix);
}

void DFS(vector<vector<int>>& adjacencyMatrix)
{
	int numberVerticles=adjacencyMatrix.size();
	vector <verticleState> stateOfVerticles(numberVerticles, {false, 0});
	stack<int>unprocessedVerticles;
	stateOfVerticles[0]={true, -1};
	unprocessedVerticles.push(0);
	while(unprocessedVerticles.empty()==false)
	{
		int currentVerticle=unprocessedVerticles.top();
		cout<<"Current: "<<currentVerticle+1<<". ";
		unprocessedVerticles.pop();
		for(int i=numberVerticles-1;i>=0;i--)
		{
			if((adjacencyMatrix[currentVerticle][i]==1)&&(stateOfVerticles[i].isVisited==false))
			{
				stateOfVerticles[i]={true, currentVerticle};
				unprocessedVerticles.push(i);
			}
		}
		printStack(unprocessedVerticles);
	}
}

void fillAdjacencyMatrix(vector<vector<int>>& adjacencyMatrix)
{
	int numberVerticles;
	cout<<"Enter number of verticles: ";
	cin>>numberVerticles;
	cout<<"(0)Manual unput (1)Random imput: ";
	int choice;
	cin>>choice;
	adjacencyMatrix.resize(numberVerticles, vector<int>(numberVerticles, 0));
	if(choice==0)
	{
		for(int i=0;i<numberVerticles;i++)
		{
			for(int j=0;j<numberVerticles;j++)
			{
				cin>>adjacencyMatrix[i][j];
			}
		}
	}
	else
	{
		for(int i=0;i<numberVerticles;i++)
		{
			for(int j=0;j<rand()%numberVerticles;j++)
			{
				int randomIndex=rand()%numberVerticles;
				int randValue=rand()%2;
				adjacencyMatrix[i][randomIndex]=randValue;
				adjacencyMatrix[randomIndex][i]=randValue;	
			}
		}
		for(int i=0;i<numberVerticles-1;i++)
		{
			adjacencyMatrix[i][i+1]=1;
			adjacencyMatrix[i+1][i]=1;
		}
		int last=numberVerticles-1;
		adjacencyMatrix[last][0]=1;
		adjacencyMatrix[0][last]=1;
		printMatrix(adjacencyMatrix);
	}
}

void printStack(stack<int> unprocessedVerticles)
{
	cout<<"Stack: ";
	while(unprocessedVerticles.empty()==false)
	{
		cout<<"v"<<unprocessedVerticles.top()+1<<" ";
		unprocessedVerticles.pop();
	}
	cout<<endl;
}
void printMatrix(const vector<vector<int>>& matrix)
{
	for(int i=0;i<matrix.size();i++)
	{
		for(int j=0;j<matrix[i].size();j++)
		{
			cout<<matrix[i][j]<<" ";
		}
		cout<<endl;
	}
}
