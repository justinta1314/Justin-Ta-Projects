#ifndef Node_h
#define Node_h

#include "Seat.h"
class Node
{
    private:
        Seat payload;
        Node *next;
        Node *down;
    public:
        Node();
        Node(Seat &);
        Seat& getSeat();
        Node* getNext() const;
        Node* getDown() const;
        void setDown(Node *);
        void setNext(Node *);
        
        friend std::ostream& operator<<(std::ostream&, Node&);
};
#endif
