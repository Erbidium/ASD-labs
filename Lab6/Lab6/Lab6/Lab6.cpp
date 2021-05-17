#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>

using namespace std;

vector<int> getArrayFromUser();
void shellSort(vector<int>&array);
//vector<int> getPrattSequence(int arraySize);
vector<int> getPrattSequence(int arraySize);
bool isGreater(int param1, int param2, int&counter);
bool isGreaterOrEquals(int param1, int param2, int&counter);
void printArray(vector<int>array);

int main()
{
	srand(time(NULL));
    vector<int>array=getArrayFromUser();
	int arraySize=array.size();
	ofstream outArray("arrayBeforeSort.txt");
	for(int i=0;i<arraySize;i++)
	{
		outArray<<array[i]<<' ';
	}
	outArray<<endl;
	outArray.close();
	cout<<"Before sort: "<<endl;
	printArray(array);
	cout<<endl;
	shellSort(array);
	cout<<endl<<"After sort: "<<endl;
	printArray(array);
	ofstream outResults("arraySorted.txt");
	for(int i=0;i<arraySize;i++)
	{
		outResults<<array[i]<<' ';
	}
	outArray<<endl;
	outArray.close();
}

vector<int> getArrayFromUser()
{
	cout<<"Generate sequence(0) Manual array input(1): ";
	int choice;
	cin>>choice;
	cout<<"Enter size of array: ";
	int arraySize;
	cin>>arraySize;
	vector<int> array(arraySize);
	if(choice==0)
	{
		cout<<"Random numbers(0) Ordered array(1) Reverse ordered array(2): ";
		int arrayType;
		cin>>arrayType;
		if(arrayType==0)
		{
			for(int i=0;i<arraySize;i++)
			{
				array[i]=rand();
			}
		}
		else if(arrayType==1)
		{
			for(int i=0;i<arraySize;i++)
			{
				array[i]=i+1;
			}
		}
		else if(arrayType==2)
		{
			int value=1;
			for(int i=arraySize-1;i>=0;i--)
			{
				array[i]=value;
				value++;
			}
		}
	}
	else if(choice==1)
	{
		for(int i=0;i<arraySize;i++)
			{
				int tempVar;
				cin>>tempVar;
				array[i]=tempVar;
			}
	}
	return array;
}
/*
vector<int> getPrattSequence(int arraySize)
{
	int i=0, j=0;
	vector<int> prattSequence;
	while((pow(2, i)*pow(3, j)<=arraySize/2))
	{
		while(pow(2, i)*pow(3, j)<=arraySize/2)
		{
			prattSequence.push_back(pow(2, i)*pow(3, j));
			j++;
		}
		i++;
		j=0;
	}
	sort(prattSequence.begin(), prattSequence.end());
	cout<<"Pratt sequence: "<<endl;
	for(int i=0;i<prattSequence.size();i++)
	{
		cout<<prattSequence[i]<<' ';
	}
	cout<<endl;
	return prattSequence;
}*/

vector<int> getPrattSequence(int arraySize)
{
	int minimal=-1;
	bool wasNewElement=false;
	vector<int> prattSequence(1, 1);
	do
	{
		wasNewElement=false;
		minimal=-1;
		for(int i=0;i<prattSequence.size();i++)
		{
			if((prattSequence[i]*2<=arraySize/2)&&(prattSequence[i]*2>prattSequence[prattSequence.size()-1]))
			{
				if((minimal==-1)||(prattSequence[i]*2<minimal))
					minimal=2*prattSequence[i];
			}
			if((prattSequence[i]*3<=arraySize/2)&&(prattSequence[i]*3>prattSequence[prattSequence.size()-1]))
			{
				if((minimal==-1)||(prattSequence[i]*3<minimal))
					minimal=3*prattSequence[i];
			}
		}
		if(minimal!=-1)
		{
			prattSequence.push_back(minimal);
			wasNewElement=true;
		}
	}
	while(wasNewElement==true);
	cout<<"Pratt sequence2: "<<endl;
	for(int i=0;i<prattSequence.size();i++)
	{
		cout<<prattSequence[i]<<' ';
	}
	cout<<endl;
	return prattSequence;
}

void shellSort(vector<int>&array)
{
	int numberOfComparisons=0, numberOfExchanges=0, size=array.size();
	vector<int>prattSequence=getPrattSequence(size);
	for(int k=prattSequence.size()-1;k>=0;k--)
	{
		numberOfComparisons++;
		for(int i=prattSequence[k];i<size;i++)
		{
			numberOfComparisons++;
			int temp=array[i];
			int j=i;
			while(isGreaterOrEquals(j, prattSequence[k],numberOfComparisons) && isGreater(array[j - prattSequence[k]],  temp, numberOfComparisons))
			{
				numberOfExchanges++;
				array[j] = array[j - prattSequence[k]];
				j-=prattSequence[k];
			}
            array[j] = temp;
		}
	}
	cout<<"Number of exhanges: "<<numberOfExchanges<<endl;
	cout<<"Number of comparisons: "<<numberOfComparisons<<endl;
}

bool isGreater(int param1, int param2, int&counter)
{
	counter++;
	return (param1>param2)?true:false;
}
bool isGreaterOrEquals(int param1, int param2, int&counter)
{
	counter++;
	return (param1>=param2)?true:false;
}

void printArray(vector<int>array)
{
	for(int i=0;i<array.size();i++)
	{
		cout<<array[i]<<' ';
	}
	cout<<endl;
}