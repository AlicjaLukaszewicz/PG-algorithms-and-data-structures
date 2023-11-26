#ifndef DOUBLYLINKEDLIST_LINKEDLIST_H
#define DOUBLYLINKEDLIST_LINKEDLIST_H
#include "Node.h"
#define NUMBER_OF_ITERATORS 10

class LinkedList {
    Node* BEG;
    Node* END;
    Node* iterators[NUMBER_OF_ITERATORS];
    int size;

    void RemoveBEG(Node* nodeToDelete);
    void RemoveEND(Node* nodeToDelete);
public:
    LinkedList();

    Node* getNodeAtIndex(int index) const;
    Node* getIterator(int number) const;
    int getSize() const;

    void InitializeIterator(int number, int index);
    void MoveIteratorForward(int number);
    void MoveIteratorBackwards(int number);

    void InsertBefore(Node* currentNode, unsigned long long int value);
    void InsertAfter(Node* currentNode, unsigned long long int value);

    void Remove(Node* nodeToDelete);

    void PrintAll() const;
    void PrintIterator(int number) const;

    ~LinkedList();
};

#endif //DOUBLYLINKEDLIST_LINKEDLIST_H
