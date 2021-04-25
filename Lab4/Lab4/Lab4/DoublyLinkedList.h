#pragma once
#include <string>

class Node
{
public:
	Node(std::string word):
	next(nullptr), previous(nullptr), word(word){}
	~Node(){delete next;}
	Node * next;
	Node * previous;
	std::string word;
};

class DoublyLinkedList
{
public:
	DoublyLinkedList();
	~DoublyLinkedList();
	void push_back(std::string word);
	void pop_back();
	void push_front(std::string word);
	void pop_front();
	void initList();
	void printPairWordsFromHead()const;
	void printUnpairedWordsFromTail()const;
	bool isEmpty()const;
	int getSize() const;
	std::string back()const;
	std::string front()const;
private:
	Node * head;
	Node * tail;
	int size;
};

