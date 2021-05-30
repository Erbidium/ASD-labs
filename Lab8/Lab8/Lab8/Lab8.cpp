#include <vector>
#include <string>
#include <iostream>
#include <set>
#include <ctime>
#include <iomanip>
#include <fstream>


using namespace std;

#define mmix(h,k) { k *= m; k ^= k >> r; k *= m; h *= m; h ^= k; }

class keyAndValueGenerator
{
    set<string> generatedKeys;
public:
    auto generateNewPair()
    {
        int numberOfSymbolsInKey=rand()%20+1;
        string key;
        do
        {
            for(int i=0;i<numberOfSymbolsInKey;i++)
            {
                key+=rand()%60+60;
            }
        }while(generatedKeys.count(key)!=0);
        string value;
        int numberOfSymbolsInValue=rand()%200+1;
        for(int i=0;i<numberOfSymbolsInValue;i++)
        {
            value+=rand()%24+97;
        }
        return make_pair(key, value);
        
    }
};

typedef pair<string, string> pairTable;

unsigned int MurmurHash2A ( const char* key, int len, unsigned int seed)
{
    const unsigned int m = 0x5bd1e995;
    const int r = 24;
    unsigned int l = len;
    const char * data=key;
    unsigned int h = seed;
    unsigned int k;
    while(len >= 4)
    {
        k = *(unsigned int*)data;
        mmix(h,k);
        data += 4;
        len -= 4;
    }
    unsigned int t = 0;
    switch(len)
    {
        case 3: t ^= data[2] << 16;
        case 2: t ^= data[1] << 8;
        case 1: t ^= data[0];
    }
    mmix(h,t)
    mmix(h,l)
    h^=h>>13;
    h*=m;
    h^= h >> 15;
    return h;
}

class hashTable
{
    vector<pairTable*> data;
    int maxSize;
    int size;
	double resizeKoef;
public:
    hashTable():
    maxSize(16),
	size(0),
	resizeKoef(0.75),
    data(16, nullptr)
    {}
    ~hashTable()
    {
        for (auto& i: data)
			delete i;
    }
    void resize()
    {
        int previousMaxSize=maxSize;
        maxSize*=2;
        size = 0;
        vector<pairTable*> newData(maxSize, nullptr);
        swap(data, newData);
        for (int i=0;i<previousMaxSize;i++)
        {
            if(newData[i]!=nullptr)
                insert(*newData[i]);
            delete newData[i];
        }
    }
    void insert(pair<string, string> value)
    {
        if (size + 1 > (int)(resizeKoef * maxSize))
            resize();
        unsigned int h1 = MurmurHash2A(value.first.data(),value.first.size(), maxSize);
        unsigned int h2 = 1+MurmurHash2A(value.first.data(),value.first.size()-1, maxSize);
        h2=h2+((h2%2)?0:1);
        int i = 0;
        while((data[(h1+h2*i)%maxSize] != nullptr)&&(i<maxSize))
        {
            i++;
        }
        {
            data[(h1+h2*i)%maxSize]=new pairTable(value);
            size++;
        }  
    }
    
    bool find(string key, string&value, int &numberOfComparisons)
    {
        numberOfComparisons=0;
	    unsigned int h1 = MurmurHash2A(key.data(),key.size(), maxSize);
        unsigned int h2 = 1+MurmurHash2A(key.data(),key.size()-1, maxSize);
        h2=h2+((h2%2)?0:1);
    	int i=0;
    	while((data[(h1+h2*i)%maxSize]!=nullptr)&&(i<maxSize))
        {
            numberOfComparisons++;
            if(data[(h1+h2*i)%maxSize]->first==key)
            {
                value=data[(h1+h2*i)%maxSize]->second;
                return true;
            }
            i++;
        }
    	return false;
    }
	void print()
    {
	    for(int i=0;i<data.size();i++)
	    {
            if(data[i]!=nullptr)
		        cout<<"i: "<<i<<" key: "<<data[i]->first<<" value: "<<data[i]->second<<endl;
	    }
    }
    int getSize(){return size;}
    int getMaxSize(){return maxSize;}
};

int main()
{
    srand(time(NULL));
    keyAndValueGenerator newGen;
    hashTable myTable;
    int numberOfElements;
    cout<<"Enter number of elements in hash table: ";
    cin>>numberOfElements;
    cout<<"Enter name of file: ";
    string fileName;
    cin>>fileName;
    ofstream outFile(fileName);
    for(int i=0;i<numberOfElements;i++)
    {
        auto newPair=newGen.generateNewPair();
        outFile<<i<<' '<<newPair.first<<' '<<newPair.second<<endl;
        myTable.insert(newPair);
    }
    outFile.close();
    string foundValue;
    int numberOfComparisons;
    string key;
    cout<<"Enter key, which you want to find: ";
    cin>>key;
    if(myTable.find(key, foundValue, numberOfComparisons))
    {
        cout<<"key: "<<key<<" value: "<<foundValue<<endl;
        cout<<"Number of comparisons: "<<numberOfComparisons<<endl;
    }
    else
    {
        cout<<"Not found!\n";
    }
}