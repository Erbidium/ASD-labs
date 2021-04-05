#include <iostream>
#include <vector>
#include <stack>
#include <ctime>
#include <iomanip>

using namespace std;

void DFS(vector<vector<int>>& adjacencyMatrix);
void fillAdjacencyMatrix(vector<vector<int>>& adjacencyMatrix);
void manualInputdAjacencyMatrix(vector<vector<int>>& adjacencyMatrix);
void manualInputdEdjesList(vector<vector<int>>& adjacencyMatrix);
void randomFillAjacencyMatrix(vector<vector<int>>& adjacencyMatrix);
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
	int numberVerticles=adjacencyMatrix.size(), currentDFSNumber=1;
	vector <int> dfsNumbers(numberVerticles, 0);
	stack<int>unprocessedVerticles;
	dfsNumbers[0]=currentDFSNumber;
	unprocessedVerticles.push(0);
	cout<<"Verticle: v1\tDFS number: "<<currentDFSNumber<<"\t";
	printStack(unprocessedVerticles);
	while(unprocessedVerticles.empty()==false)
	{
		int currentVerticle=unprocessedVerticles.top();
		bool newVisited=false;
		int i=0;
		while((i<numberVerticles)&&(newVisited==false))
		{
			if((adjacencyMatrix[currentVerticle][i]==1)&&(dfsNumbers[i]==0))
			{
				dfsNumbers[i]=++currentDFSNumber;
				unprocessedVerticles.push(i);
				cout<<"Verticle: v"<<i+1<<"\tDFS number: "<<currentDFSNumber<<"\t";
				printStack(unprocessedVerticles);
				newVisited=true;
			}
			i++;
		}
		if(newVisited==false)
		{
			unprocessedVerticles.pop();
			cout<<"Verticle: - \tDFS number: - \t";
			printStack(unprocessedVerticles);	
		}
	}
}

void fillAdjacencyMatrix(vector<vector<int>>& adjacencyMatrix)
{
	int numberVerticles, choice;
	cout<<"(0)Manual input (1)Random imput: ";
	cin>>choice;
	cout<<"Enter number of verticles: ";
	cin>>numberVerticles;
	adjacencyMatrix.resize(numberVerticles, vector<int>(numberVerticles, 0));
	if(choice==0)
	{
		int choiceType;
		cout<<"(0)Adjacency matrix (1)List of edjes: ";
		cin>>choiceType;
		if(choiceType==0)
		{
			manualInputdAjacencyMatrix(adjacencyMatrix);
		}
		else
		{
			manualInputdEdjesList(adjacencyMatrix);
			printMatrix(adjacencyMatrix);
		}
	}
	else
	{
		randomFillAjacencyMatrix(adjacencyMatrix);
		printMatrix(adjacencyMatrix);
	}
}

void manualInputdAjacencyMatrix(vector<vector<int>>& adjacencyMatrix)
{
	int numberVerticles=adjacencyMatrix.size();
	for(int i=0;i<numberVerticles;i++)
	{
		for(int j=0;j<numberVerticles;j++)
		{
			cin>>adjacencyMatrix[i][j];
		}
	}
}

void manualInputdEdjesList(vector<vector<int>>& adjacencyMatrix)
{
	int numberEdges, numberVerticles=adjacencyMatrix.size();
	cout<<"Enter number of edges: ";
	cin>>numberEdges;
	for(int i=0;i<numberEdges;i++)
	{
		int edgeBegin, edgeEnd;
		cout<<"Begin: ";
		cin>>edgeBegin;
		cout<<"End: ";
		cin>>edgeEnd;
		adjacencyMatrix[edgeBegin-1][edgeEnd-1]=1;
		adjacencyMatrix[edgeEnd-1][edgeBegin-1]=1;
	}
}

void randomFillAjacencyMatrix(vector<vector<int>>& adjacencyMatrix)
{
	int numberVerticles=adjacencyMatrix.size();
	for(int i=0;i<numberVerticles;i++)
	{
		for(int j=0;j<numberVerticles;j++)
		{
			int randValue=rand()%2;
			adjacencyMatrix[i][j]=randValue;
			adjacencyMatrix[j][i]=randValue;	
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
}

void printStack(stack<int> unprocessedVerticles)
{
	cout<<"Stack: ";
	stack<int> stackElems;
	if(unprocessedVerticles.empty()==true)
	{
		cout<<"-";
	}
	else
	{
		while(unprocessedVerticles.empty()==false)
		{
			stackElems.push(unprocessedVerticles.top());
			unprocessedVerticles.pop();
		}
		while(stackElems.empty()==false)
		{
			cout<<"v"<<left<<setw(3)<<stackElems.top()+1<<" ";
			stackElems.pop();
		}
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
