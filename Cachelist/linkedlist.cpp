#include "LinkedList.h"
#include <iostream>
using namespace std;

int LinkedList::getSize() const {
    return this->size;
}
Node *LinkedList::getNodeAtIndex(int index) const {
    Node* temp = BEG;
    for (int i = 0; i < index; ++i) {
        temp = temp->next;
    }
    return temp;
}
Node *LinkedList::getIterator(int number) const {
    Node* temp = BEG;
    while (temp != iterators[number]) {
        temp = temp->next;
    }
    return temp;
}

void LinkedList::InsertBefore(Node* currentNode, unsigned long long int value) {
    Node* newNode = new Node(value);
    if (size == 0) {
        BEG = newNode;
        END = newNode;
    } else if (size == 1) {
        newNode->next = BEG;
        END->prev = newNode;
        BEG = newNode;
    } else {
        newNode->prev = currentNode->prev;
        newNode->next = currentNode;
        if (currentNode->prev != nullptr) {
            currentNode->prev->next = newNode;
            currentNode->prev = newNode;
        } else {
            currentNode->prev = newNode;
            BEG = newNode;
        }
    }
    size++;
}
void LinkedList::InsertAfter(Node* currentNode, unsigned long long int value) {
    Node* newNode = new Node(value);
    if (size == 0) {
        BEG = newNode;
        END = newNode;
    } else if (size == 1) {
        newNode->prev = BEG;
        BEG->next = newNode;
        END = newNode;
    } else {
        newNode->prev = currentNode;
        newNode->next = currentNode->next;
        if (currentNode->next != nullptr) {
            currentNode->next->prev = newNode;
            currentNode->next = newNode;
        } else {
            currentNode->next = newNode;
            END = newNode;
        }
    }
    size++;
}

void LinkedList::Remove(Node* nodeToDelete) {
    if (size == 0) {
        return;
    } else if (size == 1) {
        BEG = nullptr;
        END = nullptr;
        for (int i = 0; i < NUMBER_OF_ITERATORS; ++i) {
            if (iterators[i] != nullptr)
                iterators[i] = nullptr;
        }
    } else {
        if (nodeToDelete == BEG) {
            RemoveBEG(nodeToDelete);
        } else if (nodeToDelete == END) {
            RemoveEND(nodeToDelete);
        } else {
            for (int i = 0; i < NUMBER_OF_ITERATORS; ++i) {
                if (iterators[i] != nullptr) {
                    if (iterators[i] == nodeToDelete) {
                        MoveIteratorForward(i);
                        }
                }
            }
            nodeToDelete->next->prev = nodeToDelete->prev;
            nodeToDelete->prev->next = nodeToDelete->next;
            nodeToDelete->next = nullptr;
            nodeToDelete->prev = nullptr;

            delete nodeToDelete;
        }
    }
    size--;
}
void LinkedList::RemoveBEG(Node* nodeToDelete) {
    for (int i = 0; i < NUMBER_OF_ITERATORS; ++i) {
        if (iterators[i] != nullptr) {
            if (iterators[i] == BEG)
                MoveIteratorForward(i);
            else
                MoveIteratorBackwards(i);
        }
    }
    BEG = nodeToDelete->next;
    nodeToDelete->next->prev = nullptr;

    nodeToDelete->prev = nullptr;
    nodeToDelete->next = nullptr;

    delete nodeToDelete;
}
void LinkedList::RemoveEND(Node* nodeToDelete) {
    for (int i = 0; i < NUMBER_OF_ITERATORS; ++i) {
        if (iterators[i] != nullptr) {
            if (iterators[i] == END)
                MoveIteratorBackwards(i);
        }
    }
    END = nodeToDelete->prev;
    nodeToDelete->prev->next = nullptr;

    nodeToDelete->prev = nullptr;
    nodeToDelete->next = nullptr;

    delete nodeToDelete;
}

void LinkedList::PrintAll() const {
    Node* tmp = BEG;
    if (size == 0)
        cout << endl;
    else if (size == 1)
        cout << tmp->getValue() << endl;
    else {
        while (tmp != nullptr) {
            cout << tmp->getValue() << " ";
            tmp = tmp->next;
        }
        cout << " " <<endl;
    }
}
void LinkedList::PrintIterator(int number) const {
    cout << iterators[number]->getValue() << endl;
}

void LinkedList::InitializeIterator(int number, int index) {
    iterators[number] = getNodeAtIndex(index);
}
void LinkedList::MoveIteratorForward(int number) {
    if(iterators[number]->next != nullptr) {
        iterators[number] = iterators[number]->next;
    }
}
void LinkedList::MoveIteratorBackwards(int number) {
    if (iterators[number]->prev != nullptr)
        iterators[number] = iterators[number]->prev;
}

LinkedList::LinkedList() {
    BEG = nullptr;
    END = nullptr;
    size = 0;
    for (int i = 0; i < NUMBER_OF_ITERATORS; ++i) {
        iterators[i] = nullptr;
    }
}
LinkedList::~LinkedList() {
    Node* current = BEG;
    Node* next;

    while (current != nullptr) {
        next = current->next;
        delete current;
        current = next;
    }
}