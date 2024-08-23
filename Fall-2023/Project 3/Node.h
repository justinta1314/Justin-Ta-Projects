#ifndef Node_h
#define Node_h

#include <iostream>

template <typename T>
class Node
{
    private:
        Node<T> *left;
        Node<T> *right;
        T payload;
    public:
        Node();
        Node(T data) { payload = data; left = nullptr; right = nullptr; }
        void setPayload(T data) { payload = data; }
        T& getPayload() { return payload; }
        void setLeft(Node<T> *l) { left = l; }
        void setRight(Node<T> *r) { right = r; }
        Node<T>* getLeft() const { return left; }
        Node<T>* getRight() const { return right; }
        template <typename t>
        friend std::ostream& operator<<(std::ostream&, const Node<t>&);
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const Node<T>& obj)
{
    out << obj.getPayload();
    return out;
}

#endif
