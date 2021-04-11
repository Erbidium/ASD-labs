#include <iostream>
#include <iomanip>
#include <vector>
#include <ctime>

const int inf=INT_MAX;

using namespace std;

void fillAdjacencyMatrix(vector<vector<int>>& adjacencyMatrix);
void manualInputdAjacencyMatrix(vector<vector<int>>& adjacencyMatrix);
void randomFillAjacencyMatrix(vector<vector<int>>& adjacencyMatrix);
void printMatrix(const vector<vector<int>>& matrix, bool isMatrixP=false);
int getSum(int number1, int number2);
void DantzigAlgorithm(vector<vector<int>>& adjacencyMatrix);

int main()
{
	srand(time(NULL));
	vector<vector<int>> adjacencyMatrix;
	fillAdjacencyMatrix(adjacencyMatrix);
	DantzigAlgorithm(adjacencyMatrix);
    return 0;
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
		manualInputdAjacencyMatrix(adjacencyMatrix);
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
			if((adjacencyMatrix[i][j]==-1)||(adjacencyMatrix[i][j]==0)) adjacencyMatrix[i][j]=inf;
		}
		adjacencyMatrix[i][i]=0;
	}

}

void randomFillAjacencyMatrix(vector<vector<int>>& adjacencyMatrix)
{
	int numberVerticles=adjacencyMatrix.size();
	for(int i=0;i<numberVerticles;i++)
	{
		for(int j=0;j<numberVerticles;j++)
		{
			adjacencyMatrix[i][j]=inf;
			int chance=rand()%2;
			int rowOrColumn=rand()%2;
			if(chance==0)
			{
				if(rowOrColumn==0)
				{
					adjacencyMatrix[i][j]=rand()%10+1;
					adjacencyMatrix[j][i]=inf;
				}
				else
				{
					adjacencyMatrix[j][i]=rand()%10+1;
					adjacencyMatrix[i][j]=inf;	
				}
			}
		}
		adjacencyMatrix[i][i]=0;
	}
}

void printMatrix(const vector<vector<int>>& matrix, bool isMatrixP)
{
	int numberVerticles=matrix.size();
	for(int i=0;i<numberVerticles;i++)
	{
		if(isMatrixP==false)
		{
			for(int j=0;j<numberVerticles;j++)
			{
				if(matrix[i][j]==inf) cout<<setw(3)<<-1<<" ";
				else cout<<setw(3)<<matrix[i][j]<<" ";
			}
		}
		else
		{
			for(int j=0;j<numberVerticles;j++)
			{
				if(matrix[i][j]==inf) cout<<"  - ";
				else cout<<setw(3)<<matrix[i][j]<<" ";
			}
		}
		cout<<endl;
	}
}

int getSum(int number1, int number2)
{
	if((number1==inf)||(number2==inf)) return inf;
	else return number1+number2;
}

void DantzigAlgorithm(vector<vector<int>>& adjacencyMatrix)
{
	vector<vector<vector<int>>> matrixD(adjacencyMatrix.size()+1);
	matrixD[0]=adjacencyMatrix;
	int numberVerticles=matrixD[0].size();
	cout<<endl<<"matrix D[0]:"<<endl;
	printMatrix(matrixD[0]);
	for(int m=1;m<=numberVerticles;m++)
	{
		matrixD[m]=vector<vector<int>>(m, vector<int>(m));
		for(int i=0;i<m-1;i++)
		{
			matrixD[m][i][m-1]=getSum(matrixD[m-1][i][0], matrixD[0][0][m-1]);
			matrixD[m][m-1][i]=getSum(matrixD[0][m-1][0], matrixD[m-1][0][i]);
			for(int j=0;j<m-1;j++)
			{
				matrixD[m][i][j]=min(getSum(matrixD[m-1][i][m-2], matrixD[m-1][m-2][j]), matrixD[m-1][i][j]);
				if(matrixD[m][i][m-1]>getSum(matrixD[m-1][i][j], matrixD[0][j][m-1]))
				{
					matrixD[m][i][m-1]=getSum(matrixD[m-1][i][j], matrixD[0][j][m-1]);
				}
				if(matrixD[m][m-1][i]>getSum(matrixD[0][m-1][j], matrixD[m-1][j][i]))
				{
					matrixD[m][m-1][i]=getSum(matrixD[0][m-1][j], matrixD[m-1][j][i]);
				}
			}
			matrixD[m][i][i]=0;
		}
		matrixD[m][m-1][m-1]=0;
		cout<<endl<<"matrix D["<<m<<"]:"<<endl;
		printMatrix(matrixD[m]);
	}
	vector<vector<int>> matrixP(numberVerticles, vector<int>(numberVerticles));
	for(int i=0;i<numberVerticles;i++)
	{
		for(int j=0;j<numberVerticles;j++)
		{
			if((matrixD[numberVerticles][i][j]!=inf)&&(matrixD[numberVerticles][i][j]!=0))
			{
				bool flag=false;
				for(int k=0;k<numberVerticles;k++)
				{
					if((matrixD[numberVerticles][i][k]+matrixD[0][k][j]==matrixD[numberVerticles][i][j])&&(flag==false))
					{
						matrixP[i][j]=k+1;
						flag=true;
					}
				}
			}
			else matrixP[i][j]=inf;
		}
	}
	cout<<endl<<"matrix p[i][j]:"<<endl;
	printMatrix(matrixP, true);
}