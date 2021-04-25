#include <iostream>
#include "DoublyLinkedList.h"

using namespace std;

int main()
{
	DoublyLinkedList list;
	list.initList();
	list.printPairWordsFromHead();
	list.printUnpairedWordsFromTail();
}