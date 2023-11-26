#ifndef DOUBLYLINKEDLIST_NODE_H
#define DOUBLYLINKEDLIST_NODE_H

class Node {
    unsigned long long int value;
public:
    Node *next;
    Node *prev;

    Node();

    explicit Node(unsigned long long int value);

    unsigned long long int getValue() const;

    ~Node();
};


#endif //DOUBLYLINKEDLIST_NODE_H
