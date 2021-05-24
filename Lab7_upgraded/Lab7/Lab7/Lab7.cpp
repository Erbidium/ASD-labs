#include <iostream>
#include <ctime>
#include <fstream>
#include <algorithm>

using namespace std;

void generateFile(const string& fileName, int numberOfElements);
void directMergeSort(const string& fileA, int numberOfElements);
void divideSequences(const string& fileA, const string& fileB, const string& fileC, bool& sortIsFinished, int sequenceToFile, int numberOfElements);
void mergeSequences(const string& fileA, const string& fileB, const string& fileC, int sequenceToFile, int numberOfElements);

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
	ofstream outFile(fileName, ios::binary);
	for(int i=0;i<numberOfElements;i++)
	{
		int number=rand()%1000000;
		outFile.write((char*)&number, sizeof(int));
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
	const int chunkSize=65536;
	int *array=new int[chunkSize];
	ifstream inFileA(fileA);
	int i=0;
	while(i<numberOfElements)
	{
		int readBufLength=min(chunkSize, numberOfElements-i);
		inFileA.read((char*)array, readBufLength*sizeof(int));
		sort(array, array+readBufLength);
		i+=readBufLength;
		cout<<"i: "<<i<<endl;
	}
	delete[] array;
	int sequenceToFile=chunkSize;
	bool sortIsFinished=false;
	do
	{
		divideSequences(fileA, fileB, fileC, sortIsFinished, sequenceToFile, numberOfElements);
		if(!sortIsFinished)
			mergeSequences(fileA, fileB, fileC, sequenceToFile, numberOfElements);
		sequenceToFile*=2;
	}
	while(!sortIsFinished);
}

void divideSequences(const string& fileA, const string& fileB, const string& fileC, bool& sortIsFinished, int sequenceToFile, int numberOfElements)
{
	cout<<"divide"<<endl;
	ifstream inFileA(fileA, ios::binary);
	ofstream outFileB(fileB, ios::trunc|ios::binary);
	ofstream outFileC(fileC, ios::trunc|ios::binary);
	const int chunkSize=65536;
	int *buffer=new int[chunkSize];
	int indexInBuffer=0;
	int currentBufferASize=min(chunkSize, numberOfElements);
	inFileA.read((char*)buffer, currentBufferASize*sizeof(int));
	int i=0, sequenceBLength=0, sequenceCLength=0;
	do
	{
		int iterations=0;
		//cout<<"b: ";
		int tempB=0;
		sortIsFinished=false;
		while((sequenceToFile!=iterations)&&(i<numberOfElements))
		{
			tempB=buffer[indexInBuffer];
			indexInBuffer++;
			if(indexInBuffer==currentBufferASize)
			{
				indexInBuffer=0;
				inFileA.read((char*)buffer, currentBufferASize*sizeof(int));
				currentBufferASize=min(chunkSize, numberOfElements-i);
			}
			outFileB.write((char*)&tempB, sizeof(int));
			//cout<<tempB<<" ";
			iterations++;
			sequenceBLength++;
			i++;
		}
		if((sequenceBLength==numberOfElements)||(sequenceCLength==numberOfElements))
			sortIsFinished=true;
		else
		{
			//cout<<endl;
			//cout<<"c: ";
			iterations=0;
			int tempC=0;
			
			while((sequenceToFile!=iterations)&&(i<numberOfElements))
			{
				tempB=buffer[indexInBuffer];
				indexInBuffer++;
				if(indexInBuffer==currentBufferASize)
				{
					indexInBuffer=0;
					inFileA.read((char*)buffer, currentBufferASize*sizeof(int));
					currentBufferASize=min(chunkSize, numberOfElements-i);
				}
				outFileC.write((char*)&tempC, sizeof(int));
				i++;
				//cout<<tempC<<" ";
				iterations++;
				sequenceCLength++;
			}
			//cout<<endl;
		}
	}
	while(i<numberOfElements);
	delete[] buffer;
	inFileA.close();
	outFileB.close();
	outFileC.close();
}

void mergeSequences(const string& fileA, const string& fileB, const string& fileC, int sequenceToFile, int numberOfElements)
{
	cout<<"merge: "<<endl;
	ofstream outFileA(fileA, ios::trunc);
	ifstream inFileB(fileB), inFileC(fileC);
	int indexOfMergedB=0, indexOfMergedC=0;
	int tempB=0, tempC=0;
	const int chunkSize=65536;
	int indexInBufferA=0;
	int i=0;
	int currentBufferASize=min(numberOfElements-i, chunkSize);
	int *bufferA=new int[currentBufferASize];
	bool wasReadB=false, wasReadC=false;
	do
	{
		if((wasReadB==false)&&(inFileB.read((char*)&tempB, sizeof(int))))
		{
			wasReadB=true;
		}
		if((wasReadC==false)&&(inFileC.read((char*)&tempC, sizeof(int))))
		{
			wasReadC=true;
		}
		if((wasReadB==false)&&(wasReadC==false))
			break;
		//cout<<"loop";
		if((indexOfMergedB<sequenceToFile)&&(indexOfMergedC<sequenceToFile)&&(wasReadB==true)&&(wasReadC==true))
		{
			if(tempB<=tempC)
			{
				bufferA[indexInBufferA]=tempB;
				indexInBufferA++;
				if(indexInBufferA==currentBufferASize)
				{
					indexInBufferA=0;
					outFileA.write((char*)bufferA, currentBufferASize*sizeof(int));
					currentBufferASize=min(chunkSize, numberOfElements-i);
				}
				i++;
				//cout<<" b "<<tempB;
				wasReadB=false;
				indexOfMergedB++;
			}
			else if(tempB>tempC)
			{
				bufferA[indexInBufferA]=tempC;
				indexInBufferA++;
				if(indexInBufferA==currentBufferASize)
				{
					indexInBufferA=0;
					outFileA.write((char*)bufferA, currentBufferASize*sizeof(int));
					currentBufferASize=min(chunkSize, numberOfElements-i);
				}
				i++;
				//cout<<" c "<<tempC;
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
			bufferA[indexInBufferA]=tempC;
			indexInBufferA++;
			if(indexInBufferA==currentBufferASize)
			{
				indexInBufferA=0;
				outFileA.write((char*)bufferA, currentBufferASize*sizeof(int));
				currentBufferASize=min(chunkSize, numberOfElements-i);
			}
			i++;
			//cout<<" c "<<tempC;
			wasReadC=false;
			indexOfMergedC++;
		}
		else if((indexOfMergedC==sequenceToFile)||((wasReadC==false)&&((wasReadB==true))))
		{
			bufferA[indexInBufferA]=tempB;
			indexInBufferA++;
			i++;
			if(indexInBufferA==currentBufferASize)
			{
				indexInBufferA=0;
				outFileA.write((char*)bufferA, currentBufferASize*sizeof(int));
				currentBufferASize=min(chunkSize, numberOfElements-i);
			}
			//cout<<" b "<<tempB;
			wasReadB=false;
			indexOfMergedB++;
		}
	}
	while((!inFileB.eof())||(!inFileC.eof()));
	if(indexInBufferA>0)
		outFileA.write((char*)bufferA, currentBufferASize);
	delete[]bufferA;
	//cout<<endl;
}
