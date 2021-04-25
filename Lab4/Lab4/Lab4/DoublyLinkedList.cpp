#include "DoublyLinkedList.h"
#include <iostream>

using namespace std;

DoublyLinkedList::DoublyLinkedList():
head(nullptr), tail(nullptr), size(0)
{}

DoublyLinkedList::~DoublyLinkedList()
{
	delete head;
}

int DoublyLinkedList::getSize() const
{
	return size;
}

void DoublyLinkedList::push_back(string word)
{
	Node * newNode=new Node(word);
	if((tail==nullptr)&&(head==nullptr))
	{
		tail=head=newNode;
	}
	else
	{
		newNode->previous=tail;
		tail->next=newNode;
		tail=newNode;
	}
	size++;
}

void DoublyLinkedList::pop_back()
{
	Node * tempNode=tail;
	tail=tail->previous;
	tail->next=nullptr;
	delete tempNode;
	size--;
}

void DoublyLinkedList::push_front(string word)
{
	Node * newNode=new Node(word);
	if((tail==nullptr)&&(head==nullptr))
	{
		tail=head=newNode;
	}
	else
	{
		newNode->next=head;
		head->previous=newNode;
		head=newNode;
	}
	size++;	
}

void DoublyLinkedList::pop_front()
{
	Node * tempNode=head;
	head=head->next;
	head->previous=nullptr;
	tempNode->next=nullptr;
	delete tempNode;
	size--;
}

string DoublyLinkedList::back()const
{
	return tail->word;
}

string DoublyLinkedList::front()const
{
	return head->word;
}

bool DoublyLinkedList::isEmpty()const
{
	return (size==0)?true:false;
}

void DoublyLinkedList::printPairWordsFromHead()const
{
	cout<<"Words on paired positions, starting from head:\n";
	Node * current=head;
	for(int i=1;i<=size;i++)
	{
		if(i%2==0)
		{
			cout<<current->word<<" ";
		}
		current=current->next;
	}
	cout<<endl;
}

void DoublyLinkedList::printUnpairedWordsFromTail()const
{
	cout<<"Words on unpaired positions, starting from tail:\n";
	Node * current=tail;
	for(int i=size;i>0;i--)
	{
		if(i%2==1)
		{
			cout<<current->word<<" ";	
		}
		current=current->previous;
	}
	cout<<endl;
}

void DoublyLinkedList::initList()
{
	cout<<"Enter number of words:\n";
	int numberWords;
	cin>>numberWords;
	string tempWord;
	cout<<"Enter words:\n";
	for(int i=0;i<numberWords;i++)
	{
		cin>>tempWord;
		push_back(tempWord);
	}
}
