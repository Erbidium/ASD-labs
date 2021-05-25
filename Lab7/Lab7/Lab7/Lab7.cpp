#include <iostream>
#include <ctime>
#include <fstream>

using namespace std;

void generateFile(const string& fileName, int numberOfElements);
void directMergeSort(const string& fileA, int numberOfElements);
void divideSequences(const string& fileA, const string& fileB, const string& fileC, bool& sortIsFinished, int sequenceToFile, int numberOfElements);
void mergeSequences(const string& fileA, const string& fileB, const string& fileC, int sequenceToFile);

int main()
{
	srand(time(NULL));
    cout<<"Generate array(0) Sort array(1): ";
	int choice;
	cin>>choice;
	cout<<"Enter number of elements: ";
	int numberOfElements;
	cin>>numberOfElements;
	cout<<"Enter name of file: ";
	string fileName;
	cin>>fileName;
	if(choice==0)
		generateFile(fileName, numberOfElements);
	else
	{
		ifstream inFileA(fileName);
		if(inFileA.is_open())
		{
			inFileA.close();
			directMergeSort(fileName, numberOfElements);
		}
		else
		{
			cout<<"Cannot open a file!"<<endl;
		}
	}
}

void generateFile(const string& fileName, int numberOfElements)
{
	ofstream outFile(fileName);
	for(int i=0;i<numberOfElements;i++)
	{
		outFile<<rand()%1000000<<' ';
	}
	outFile.close();
}

void directMergeSort(const string& fileA, int numberOfElements)
{
	string fileB=fileA;
	string fileC=fileB;
	int dotPos=fileA.find('.');
	fileB.insert(dotPos, "B");
	fileC.insert(dotPos, "C");
	int sequenceToFile=4;
	bool sortIsFinished=false;
	do
	{
		divideSequences(fileA, fileB, fileC, sortIsFinished, sequenceToFile, numberOfElements);
		if(!sortIsFinished)
			mergeSequences(fileA, fileB, fileC, sequenceToFile);
		sequenceToFile*=2;
	}
	while(!sortIsFinished);
}

void divideSequences(const string& fileA, const string& fileB, const string& fileC, bool& sortIsFinished, int sequenceToFile, int numberOfElements)
{
	ifstream inFileA(fileA);
	ofstream outFileB(fileB, ios::trunc);
	ofstream outFileC(fileC, ios::trunc);
	int i=0, sequenceBLength=0, sequenceCLength=0;
	do
	{
		int iterations=0;
		int tempB=0;
		sortIsFinished=false;
		while((sequenceToFile!=iterations)&&(i<numberOfElements))
		{
			inFileA>>tempB;
			outFileB<<tempB<<" ";
			iterations++;
			sequenceBLength++;
			i++;
		}
		if((sequenceBLength==numberOfElements)||(sequenceCLength==numberOfElements))
			sortIsFinished=true;
		else
		{
			iterations=0;
			int tempC=0;
			while((sequenceToFile!=iterations)&&(i<numberOfElements))
			{
				inFileA>>tempC;
				outFileC<<tempC<<" ";
				iterations++;
				sequenceCLength++;
				i++;
			}
		}
	}
	while(i<numberOfElements);
	inFileA.close();
	outFileB.close();
	outFileC.close();
}

void mergeSequences(const string& fileA, const string& fileB, const string& fileC, int sequenceToFile)
{
	ofstream outFileA(fileA, ios::trunc);
	ifstream inFileB(fileB), inFileC(fileC);
	int indexOfMergedB=0, indexOfMergedC=0;
	int tempB=0, tempC=0;
	bool wasReadB=false, wasReadC=false;
	do
	{
		if((wasReadB==false)&&(inFileB>>tempB))
		{
			wasReadB=true;
		}
		if((wasReadC==false)&&(inFileC>>tempC))
		{
			wasReadC=true;
		}
		if((wasReadB==false)&&(wasReadC==false))
			break;
		if((indexOfMergedB<sequenceToFile)&&(indexOfMergedC<sequenceToFile)&&(wasReadB==true)&&(wasReadC==true))
		{
			if(tempB<=tempC)
			{
				outFileA<<tempB<<" ";
				wasReadB=false;
				indexOfMergedB++;
			}
			else if(tempB>tempC)
			{
				outFileA<<tempC<<" ";
				wasReadC=false;
				indexOfMergedC++;
			}
		}
		else if((indexOfMergedB==sequenceToFile)&&(indexOfMergedC==sequenceToFile))
		{
			indexOfMergedB=0;
			indexOfMergedC=0;
		}
		else if((indexOfMergedB==sequenceToFile)||((wasReadB==false)&&(wasReadC==true)))
		{
			outFileA<<tempC<<" ";
			wasReadC=false;
			indexOfMergedC++;
		}
		else if((indexOfMergedC==sequenceToFile)||((wasReadC==false)&&((wasReadB==true))))
		{
			outFileA<<tempB<<" ";
			wasReadB=false;
			indexOfMergedB++;
		}
	}
	while((!inFileB.eof())||(!inFileC.eof()));
}
