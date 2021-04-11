#include <vector>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stack>

using namespace std;

vector<vector<int>> readDirectDistances();
vector<vector<int>> readRoadDistances();
vector<string> readCities();
void printMatrix(vector<vector<int>>);
void bestFirstSearch(vector<vector<int>> directWays, vector<vector<int>> roads, vector<string> cities, int start, int end);
void AStar(vector<vector<int>> directWays, vector<vector<int>> roads, vector<string> cities, int start, int end);

int main()
{
	vector<vector<int>> directDistances=readDirectDistances();
	vector<vector<int>> roadDistances=readRoadDistances();
	vector<string> cities=readCities();
	cout<<"Enter two cities:\n";
	string city1, city2;
	cin>>city1>>city2;
	int index1=-1, index2=-1;
	for(int i=0;i<15;i++)
	{
		if(cities[i]==city1)
			index1=i;
		if(cities[i]==city2)
			index2=i;
	}
	if((index1!=-1)&&(index2!=-1))
	{
		cout<<"Best-first search(0) or A*(1)?"<<endl;
		int choice;
		cin>>choice;
		if(choice==0)
		{
			bestFirstSearch(directDistances, roadDistances, cities, index1, index2);
		}
		else
		{
			AStar(directDistances, roadDistances, cities, index1, index2);
		}
	}
	else
	{
		cout<<"No such cities!"<<endl;
	}
}

vector<vector<int>> readDirectDistances()
{
	ifstream inFile("C:/Users/Acer/Documents/PythonLabs/distances/direct.txt");
	vector<vector<int>> directDistances(15, vector<int>(15));
	for(int i=0;i<15;i++)
	{
		for(int j=0;j<15;j++)
			inFile>>directDistances[i][j];
	}
	return directDistances;
}

vector<vector<int>> readRoadDistances()
{
	ifstream inFile("C://Users/Acer/Documents/PythonLabs/distances/roads.txt");
	vector<vector<int>> roadDistances(15, vector<int>(15));
	for(int i=0;i<15;i++)
	{
		for(int j=0;j<15;j++)
			inFile>>roadDistances[i][j];
	}
	return roadDistances;
}

vector<string> readCities()
{
	vector<string> cities(15);
	ifstream inFile("D:/Навчання/1 курс/2 семестр/АСД/Лаб3/cities.txt");
	for(int i=0;i<15;i++)
	{
		inFile>>cities[i];
		int position=cities[i].find(",Norway");
		if(position!=string::npos) cities[i].erase(position);
	}
	return cities;
}

void printMatrix(vector<vector<int>> matrix)
{
	for(int i=0;i<15;i++)
	{
		for(int j=0;j<15;j++)
			cout<<setw(4)<<matrix[i][j]<<" ";
		cout<<endl;
	}
	cout<<endl;
}

void bestFirstSearch(vector<vector<int>> directWays, vector<vector<int>> roads, vector<string> cities, int start, int end)
{
	vector<int> closed;
	vector<int> open;
	int from[15], f[15];
	for(int i=0;i<15;i++)
	{
		from[i]=-1;
		f[i]=INT_MAX;
	}
	open.push_back(start);
	f[start]=directWays[start][end];
	while(!open.empty())
	{
		int current=open[0];
		for(int i=1;i<open.size();i++)
		{
			if(f[open[i]]<f[current]) current=open[i];
		}
		if(current==end)
		{
			stack<int>way;
			int verticle=end;			
			while(verticle!=start)
			{	
				way.push(verticle);
				verticle=from[verticle];
			}
			way.push(start);
			while(!way.empty())
			{
				cout<<cities[way.top()];
				if(way.top()!=end) cout<<'-';
				way.pop();
			}
			cout<<endl;
			return;
		}
		for(int i=0;i<open.size();i++)
		{
			if(open[i]==current) 
			{
				open.erase(open.begin()+i);
			}
		}
		closed.push_back(current);
		for(int i=0;i<15;i++)
		{
			vector<int>::iterator it;
			it=find(closed.begin(), closed.end(), i);
			vector<int>::iterator it2;
			if((roads[current][i]!=0)&&(it==closed.end()))
			{
				f[i]=directWays[i][end];
				it2=find(open.begin(), open.end(), i);
				if(it2==open.end())
					open.push_back(i);
				from[i]=current;
			}
			else if(directWays[i][end]<f[i])
			{
				f[i]=directWays[i][end];
				from[i]=current;
			}
		}
	}
	cout<<"Fail! Way is not found!"<<endl;
	
}

void AStar(vector<vector<int>> directWays, vector<vector<int>> roads, vector<string> cities, int start, int end)
{
	vector<int> closed;
	vector<int> open;
	int from[15], g[15], f[15];
	for(int i=0;i<15;i++)
	{
		from[i]=-1;
		g[i]=INT_MAX;
		f[i]=INT_MAX;
	}
	open.push_back(start);
	g[start]=0;
	f[start]=g[start]+directWays[start][end];
	while(!open.empty())
	{
		int current=open[0];
		for(int i=1;i<open.size();i++)
		{
			if(f[open[i]]<f[current]) current=open[i];
		}
		if(current==end)
		{
			stack<int>way;
			int verticle=end;			
			while(verticle!=start)
			{	
				way.push(verticle);
				verticle=from[verticle];
			}
			way.push(start);
			while(!way.empty())
			{
				cout<<cities[way.top()];
				if(way.top()!=end) cout<<'-';
				way.pop();
			}
			cout<<endl;
			cout<<"Length: "<<g[current]<<endl;
			return;
		}
		for(int i=0;i<open.size();i++)
		{
			if(open[i]==current) 
			{
				open.erase(open.begin()+i);
			}
		}
		closed.push_back(current);
		for(int i=0;i<15;i++)
		{
			vector<int>::iterator it;
			it=find(closed.begin(), closed.end(), i);
			if((roads[current][i]!=0)&&(it==closed.end()))
			{
				int temp_g=g[current]+roads[current][i];
				vector<int>::iterator it2;
				it2=find(open.begin(), open.end(), i);
				if((it2==open.end())||(temp_g<g[i]))
				{
					from[i]=current;
					g[i]=temp_g;
					f[i]=g[i]+directWays[i][end];
				}
				if(it2==open.end()) 
				{
					open.push_back(i);
				}
			}
		}
	}
	cout<<"Fail! Way is not found!"<<endl;
}