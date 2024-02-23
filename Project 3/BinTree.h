#ifndef BinTree_h
#define BinTree_h
#include "Node.h"

template <typename T>
class BinTree
{
    private:
        Node<T> *root;
        Node<T>* removeRecursive(T obj, Node<T> *r);
        void insertRecursive(T obj, Node<T> *r);
        T* searchRecursive(T key, Node<T> *r);
        void destroyTree(Node<T> *r);
    public:
        BinTree() { root = nullptr; }
        void Insert(T obj);
        void Remove(T key);
        T* Search(T key);
        void setRoot(Node<T> *r) { root = r; }
        Node<T>* getRoot() { return root; }
        void displayTree(Node<T>*);
        ~BinTree();
};

template <typename T>
void BinTree<T>::Insert(T obj)
{
    // if the tree is completely empty
    if(!root)
    {
        // make a new node and set the root to the new node
        Node<T> *newNode = new Node<T>(obj);
        root = newNode;
    }
    else
    {
        // traverse through the tree and insert the object where it belongs
        insertRecursive(obj, root);
    }
}

// private helper function
template <typename T>
void BinTree<T>::insertRecursive(T obj, Node<T> *r)
{
    if(obj < r->getPayload())
    {
        // if the current node's left pointer is nullptr
        if(!r->getLeft())
        {
            // create new node and set the current node's left pointer to the new node
            Node<T> *newNode = new Node<T>(obj);
            r->setLeft(newNode);
        }
        else
        {
            // go down to the left again since the current node is bigger than the object
            insertRecursive(obj, r->getLeft());
        }
    }
    else
    {
        // if the current node's right pointer is nullptr
        if(!r->getRight())
        {
            // create new node and set the current node's right pointer to the new node
            Node <T> *newNode = new Node<T>(obj);
            r->setRight(newNode);
        }
        else
        {
            // traverse down the current node's right side
            insertRecursive(obj, r->getRight());
        }
    }
}

template <typename T>
void BinTree<T>::Remove(T key)
{
    root = removeRecursive(key, root);
}

//private helper function
template <typename T>
Node<T>* BinTree<T>::removeRecursive(T key, Node<T> *r)
{
    // if the current node is nullptr
    if(r == nullptr)
    {
        return r;
    }
    // if key is less than the current node's payload
    if(key < r->getPayload())
    {
        // traverse down the left pointer of the current node
        r->setLeft(removeRecursive(key, r->getLeft()));
    }
    // if key is larger than the current node's payload
    else if(key > r->getPayload())
    {
        // traverse down the right pointer of the current node
        r->setRight(removeRecursive(key, r->getRight()));
    }
    // current node's payload == key
    else
    {
        // if the current node does not have a left child
        if(r->getLeft() == nullptr)
        {
            // current node's right child is returned since the current node is being removed
            Node<T> *temp = r->getRight();
            delete r;
            return temp;
        }
        // if the current node does not have a right child
        else if(r->getRight() == nullptr)
        {
            // current node's left child is returned since the current node is being removed
            Node<T> *temp = r->getLeft();
            delete r;
            return temp;
        }
        // current node has two children, so you have to find the successor (smallest in the right subtree)
        // start by going to the current node's right child
        Node<T> *succ = r->getRight();
        // since you have to get the smallest in the subtree, go left as much as you can
        while(succ->getLeft() != nullptr)
        {
            succ = succ->getLeft();
        }
        // store the successor
        Node<T> *temp = succ;
        // swap the payload of the successor and the current node
        r->setPayload(temp->getPayload());
        r->setRight(removeRecursive(temp->getPayload(), r->getRight()));
    }
    return r;
}

template <typename T>
T* BinTree<T>::Search(T key)
{
    return searchRecursive(key, root);
}

// private helper function
template <typename T>
T* BinTree<T>::searchRecursive(T key, Node<T> *r)
{
    // if the current node exists
    if(r)
    {
        // if the current node's payload == key
        if(key == r->getPayload())
        {
            // create pointer to the payload and return the pointer
            T* obj = &r->getPayload();
            return obj;
        }
        // if the current node's payload is larger than the key
        else if(key < r->getPayload())
        {
            // traverse to the left child of the current node and search
            return searchRecursive(key, r->getLeft());
        }
        // if the current node's payload is smaller than the key
        else
        {
            // traverse to the right child of the current node and search
            return searchRecursive(key, r->getRight());
        }
    }
    // if key is not found, return nullptr
    return nullptr;
}

template <typename T>
void BinTree<T>::displayTree(Node<T> *t)
{
    // if t is nullptr, don't do anything
    if(!t)
    {
        return;
    }
    // traverse the left side of the tree
    displayTree(t->getLeft());
    
    // print the current node's payload
    std::cout << t->getPayload();
    
    //traverse the right side of the tree
    displayTree(t->getRight());
}

template <typename T>
BinTree<T>::~BinTree()
{
    destroyTree(root);
}

template <typename T>
void BinTree<T>::destroyTree(Node<T> *r)
{
    if(r)
    {
        // delete the left side of the tree
        destroyTree(r->getLeft());
        // delete the right side of the tree
        destroyTree(r->getRight());
        // delete the current node
        delete r;
    }
}

#endif
