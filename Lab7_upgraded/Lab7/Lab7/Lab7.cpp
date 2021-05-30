#include <iostream>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

void generateFile(const string& fileName, int numberOfElements);
void directMergeSort(const string& fileA, int numberOfElements);
void binaryToTextFile(const string& fileName, int numberOfElements);
void divideSequences(const string& fileA, const string& fileB, const string& fileC, bool& sortIsFinished, int sequenceToFile, int numberOfElements, int &numBufB, int &numBufC);
void mergeSequences(const string& fileA, const string& fileB, const string& fileC, int sequenceToFile, int numberOfElements, int numBufB, int numBufC);

int main()
{
	srand(time(NULL));
    cout<<"Generate array(0) Sort array(1) Convert binary to text file(2): ";
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
	else if(choice==1)
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
	else
	{
		binaryToTextFile(fileName, numberOfElements);
	}
}

void generateFile(const string& fileName, int numberOfElements)
{
	ofstream outFile(fileName, ios::binary);
	const int chunkSize=262144;
	int *array=new int[chunkSize];
	int i=0;
	while(i<numberOfElements)
	{
		int bufLength=min(chunkSize, numberOfElements-i);
		for(int i=0;i<bufLength;i++)
		{
			array[i]=rand()%1000000;
		}
		outFile.write(reinterpret_cast<char*>(array), bufLength*sizeof(int));
		i+=bufLength;
	}
	outFile.close();
}

void directMergeSort(const string& fileA, int numberOfElements)
{
	string fileB=fileA;
	string fileC=fileA;
	int dotPos=fileA.find('.');
	fileB.insert(dotPos, "B");
	fileC.insert(dotPos, "C");
	const int chunkSize=262144;
	string tempFileName="temp"+fileA;
	rename(fileA.data(), tempFileName.data());
	ifstream inFileA(tempFileName, ios::binary);
	ofstream outFileA(fileA, ios::binary);
	int i=0;
	cout<<"before while"<<endl;
	vector<int> vectorBuf;
	while(i<numberOfElements)
	{
		int readBufLength=min(chunkSize, numberOfElements-i);
		vectorBuf.resize(readBufLength);
		inFileA.read(reinterpret_cast<char*>(vectorBuf.data()), readBufLength*sizeof(int));
		cout<<"before sort"<<endl;
		cout<<readBufLength<<endl;
		sort(vectorBuf.begin(), vectorBuf.end());
		cout<<i<<" "<<"sorted!"<<endl;
		outFileA.write(reinterpret_cast<char*>(vectorBuf.data()), readBufLength*sizeof(int));
		i+=readBufLength;
	}
	inFileA.close();
	outFileA.close();
	cout<<"sorted!"<<endl;
	remove(tempFileName.data());
	int sequenceToFile=chunkSize;
	bool sortIsFinished=false;
	do
	{
		int numBufB=0, numBufC=0;
		divideSequences(fileA, fileB, fileC, sortIsFinished, sequenceToFile, numberOfElements, numBufB, numBufC);
		if(!sortIsFinished)
			mergeSequences(fileA, fileB, fileC, sequenceToFile, numberOfElements, numBufB, numBufC);
		sequenceToFile*=2;
	}
	while(!sortIsFinished);
}

void binaryToTextFile(const string& fileName,int numberOfElements)
{
	ifstream inFile(fileName, ios::binary);
	int dotPos=fileName.find('.');
	string textFile=fileName;
	textFile.erase(dotPos);
	textFile.insert(dotPos, "Text.txt");
	ofstream outTxt(textFile);
	const int chunkSize=262144;
	int *array=new int[chunkSize];
	int i=0;
	while(i<numberOfElements)
	{
		int readBufLength=min(chunkSize, numberOfElements-i);
		inFile.read(reinterpret_cast<char*>(array), readBufLength*sizeof(int));
		for(int j=0;j<readBufLength;j++)
		{
			outTxt<<array[j]<<' ';
		}
		i+=readBufLength;
	}
	inFile.close();
	outTxt.close();
}

void divideSequences(const string& fileA, const string& fileB, const string& fileC, bool& sortIsFinished, int sequenceToFile, int numberOfElements, int &numBufB, int &numBufC)
{
	cout<<"divide "<<endl;
	ifstream inFileA(fileA, ios::binary);
	ofstream outFileB(fileB, ios::trunc|ios::binary);
	ofstream outFileC(fileC, ios::trunc|ios::binary);
	const int chunkSize=262144;
	int currentBufferASize=min(numberOfElements, chunkSize);
	int currentBufferBSize= chunkSize;
	int currentBufferCSize= chunkSize;
	int *bufferA=new int[chunkSize];
	int *bufferB=new int[chunkSize];
	int *bufferC=new int[chunkSize];
	int indexInBufferA=0, indexInBufferB=0, indexInBufferC=0;
	inFileA.read(reinterpret_cast<char*>(bufferA), currentBufferASize*sizeof(int));
	int posInA=0, sequenceBLength=0, sequenceCLength=0;
	int posInB=0, posInC=0;
	do
	{
		int iterations=0;
		int tempB=0;
		sortIsFinished=false;
		while((sequenceToFile!=iterations)&&(posInA<numberOfElements))
		{
			tempB=bufferA[indexInBufferA];
			indexInBufferA++;
			if(indexInBufferA==currentBufferASize)
			{
				indexInBufferA=0;
				currentBufferASize=min(chunkSize, numberOfElements-posInA);
				inFileA.read(reinterpret_cast<char*>(bufferA), currentBufferASize*sizeof(int));
			}
			
			bufferB[indexInBufferB]=tempB;
			indexInBufferB++;
			posInB++;
			if(indexInBufferB==chunkSize)
			{
				indexInBufferB=0;
				outFileB.write(reinterpret_cast<char*>(bufferB), currentBufferBSize*sizeof(int));
			}
			
			numBufB++;
			iterations++;
			sequenceBLength++;
			posInA++;
		}
		if((sequenceBLength==numberOfElements)||(sequenceCLength==numberOfElements))
			sortIsFinished=true;
		else
		{
			iterations=0;
			int tempC=0;
			
			while((sequenceToFile!=iterations)&&(posInA<numberOfElements))
			{
				tempC=bufferA[indexInBufferA];
				indexInBufferA++;
				if(indexInBufferA==currentBufferASize)
				{
					indexInBufferA=0;
					currentBufferASize=min(chunkSize, numberOfElements-posInA);
					inFileA.read(reinterpret_cast<char*>(bufferA), currentBufferASize*sizeof(int));
				}
				bufferC[indexInBufferC]=tempC;
				indexInBufferC++;
				if(indexInBufferC==chunkSize)
				{
					indexInBufferC=0;
					outFileC.write(reinterpret_cast<char*>(bufferC), currentBufferCSize*sizeof(int));
				}
				numBufC++;
				posInC++;
				posInA++;
				iterations++;
				sequenceCLength++;
			}
		}
	}
	while(posInA<numberOfElements);
	if(indexInBufferB>0)
		outFileB.write(reinterpret_cast<char*>(bufferB), indexInBufferB*sizeof(int));
	if(indexInBufferC>0)
		outFileC.write(reinterpret_cast<char*>(bufferC), indexInBufferC*sizeof(int));
	delete[] bufferA;
	delete[] bufferB;
	delete[] bufferC;
	inFileA.close();
	outFileB.close();
	outFileC.close();
}

void mergeSequences(const string& fileA, const string& fileB, const string& fileC, int sequenceToFile, int numberOfElements, int numBufB, int numBufC)
{
	cout<<"merge "<<endl;
	ofstream outFileA(fileA, ios::trunc|ios::binary);
	ifstream inFileB(fileB, ios::binary), inFileC(fileC, ios::binary);
	int indexOfMergedB=0, indexOfMergedC=0;
	int tempB=0, tempC=0;
	const int chunkSize=262144;
	int indexInBufferA=0, indexInBufferB=0, indexInBufferC=0;
	int posInA=0, posInB=0, posInC=0;
	int currentBufferASize=min(numberOfElements, chunkSize);
	int currentBufferBSize=min(numBufB, chunkSize);
	int currentBufferCSize=min(numBufC, chunkSize);
	int *bufferA=new int[chunkSize];
	int *bufferB=new int[chunkSize];
	int *bufferC=new int[chunkSize];
	inFileB.read(reinterpret_cast<char*>(bufferB), currentBufferBSize*sizeof(int));
	inFileC.read(reinterpret_cast<char*>(bufferC), currentBufferCSize*sizeof(int));
	bool wasReadB=false, wasReadC=false;
	do
	{
		if((wasReadB==false)&&(posInB<numBufB))
		{
			posInB++;
			tempB=bufferB[indexInBufferB];
			indexInBufferB++;
			if(indexInBufferB==currentBufferBSize)
			{
				indexInBufferB=0;
				currentBufferBSize=min(chunkSize, numBufB-posInB);
				inFileB.read(reinterpret_cast<char*>(bufferB), currentBufferBSize*sizeof(int));
			}
			wasReadB=true;
		}
		if((wasReadC==false)&&(posInC<numBufC))
		{
			posInC++;
			tempC=bufferC[indexInBufferC];
			indexInBufferC++;
			if(indexInBufferC==currentBufferCSize)
			{
				indexInBufferC=0;
				currentBufferCSize=min(chunkSize, numBufC-posInC);
				inFileC.read(reinterpret_cast<char*>(bufferC), currentBufferCSize*sizeof(int));
			}
			wasReadC=true;
		}
		if((wasReadB==false)&&(wasReadC==false))
			break;
		if((indexOfMergedB<sequenceToFile)&&(indexOfMergedC<sequenceToFile)&&(wasReadB==true)&&(wasReadC==true))
		{
			if(tempB<=tempC)
			{
				bufferA[indexInBufferA]=tempB;
				indexInBufferA++;
				posInA++;
				if(indexInBufferA==currentBufferASize)
				{
					indexInBufferA=0;
					outFileA.write(reinterpret_cast<char*>(bufferA), currentBufferASize*sizeof(int));
					currentBufferASize=min(chunkSize, numberOfElements-posInA);
				}
				wasReadB=false;
				indexOfMergedB++;
			}
			else if(tempB>tempC)
			{
				bufferA[indexInBufferA]=tempC;
				indexInBufferA++;
				posInA++;
				if(indexInBufferA==currentBufferASize)
				{
					indexInBufferA=0;
					outFileA.write(reinterpret_cast<char*>(bufferA), currentBufferASize*sizeof(int));
					currentBufferASize=min(chunkSize, numberOfElements-posInA);
				}
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
			posInA++;
			if(indexInBufferA==currentBufferASize)
			{
				indexInBufferA=0;
				outFileA.write(reinterpret_cast<char*>(bufferA), currentBufferASize*sizeof(int));
				currentBufferASize=min(chunkSize, numberOfElements-posInA);
			}
			wasReadC=false;
			indexOfMergedC++;
		}
		else if((indexOfMergedC==sequenceToFile)||((wasReadC==false)&&((wasReadB==true))))
		{
			bufferA[indexInBufferA]=tempB;
			indexInBufferA++;
			posInA++;
			if(indexInBufferA==currentBufferASize)
			{
				indexInBufferA=0;
				outFileA.write(reinterpret_cast<char*>(bufferA), currentBufferASize*sizeof(int));
				currentBufferASize=min(chunkSize, numberOfElements-posInA);
			}
			wasReadB=false;
			indexOfMergedB++;
		}
	}
	while(numberOfElements!=posInA);
	if(indexInBufferA>0)
		outFileA.write(reinterpret_cast<char*>(bufferA), indexInBufferA*sizeof(int));
	delete[]bufferA;
	delete[]bufferB;
	delete[]bufferC;
	outFileA.close();
	inFileB.close();
	inFileC.close();
}
