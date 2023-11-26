#include "Node.h"

Node::Node(unsigned long long int value) {
    this->value = value;
    this->next = nullptr;
    this->prev = nullptr;
}
Node::Node() {
    this->value = 0;
    this->next = nullptr;
    this->prev = nullptr;
}
unsigned long long int Node::getValue() const {
    return this->value;
}
Node::~Node() = default;
