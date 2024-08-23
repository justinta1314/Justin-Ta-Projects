#include "Node.h"

// default constructor, sets the next and down pointers to nullptr
Node::Node()
{
    this->next = nullptr;
    this->down = nullptr;
}

// overloaded constructor, sets next and down pointers to nullptr, sets payload to seat passed in
Node::Node(Seat &s)
{
    this->next = nullptr;
    this->down = nullptr;
    payload = s;
}

// returns the seat in the node
Seat& Node::getSeat()
{
    return payload;
}

// returns the next node
Node* Node::getNext() const
{
    return next;
}

// returns the down node
Node* Node::getDown() const
{
    return down;
}

// sets next pointer to n
void Node::setNext(Node *n)
{
    next = n;
}

// sets down pointer to d
void Node::setDown(Node *d)
{
    down = d;
}

std::ostream& operator<<(std::ostream &out, Node *obj)
{
    out << obj->getSeat();
    return out;
}
