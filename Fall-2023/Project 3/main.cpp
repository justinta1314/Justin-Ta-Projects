/*
Goal of the Project:
Create a templated binary search tree and use that template for a movie kiosk reservation system.
At the start of the program, read in the inventory file and the transactions file.
Store the movies in the binary search tree.
If all copies of a movie get removed, remove it from the binary search tree.
If copies of a movie are added but the movie is not in the binary search tree, insert it into the tree.
All traversals of the binary search tree are done recursively.
Test cases: 60/60
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "BinTree.h"
#include "DVD.h"

void readInventory(std::string filename, BinTree<DVD> &t);

void readTransactions(std::string filename, BinTree<DVD> &t);

int main()
{
    // prompt user for inventory file
    std::cout << "Please enter the inventory file." << std::endl;
    std::string inventoryFile;
    std::cin >> inventoryFile;
    std::ifstream inventoryInput;
    inventoryInput.open(inventoryFile);
    // if given an invalid file, the program will close
    if(!inventoryInput)
    {
        std::cout << "Invalid file name. Closing the program..." << std::endl;
        inventoryInput.close();
        return 1;
    }
    BinTree<DVD> tree;
    // create the binary tree using the inventory file
    readInventory(inventoryFile, tree);
    // prompt user for the transaction log
    std::cout << "Please enter the transaction log." << std::endl;
    std::string transactionLog;
    std::cin >> transactionLog;
    std::ifstream transactionInput;
    transactionInput.open(transactionLog);
    // if given invalid file, program will close
    if(!transactionInput)
    {
        std::cout << "Invalid file name. Closing the program..." << std::endl;
        transactionInput.close();
        return 2;
    }
    // modify the binary tree using the transactions file
    readTransactions(transactionLog, tree);
    // print the contents of the tree using inorder traversal
    tree.displayTree(tree.getRoot());
}

void readInventory(std::string filename, BinTree<DVD> &t)
{
    std::ifstream inventoryInput;
    inventoryInput.open(filename);
    std::string line;
    std::string title;
    std::string word;
    int available;
    int rented;
    while(getline(inventoryInput, line))
    {
        std::istringstream iss(line);
        // first thing in line is movie title
        std::getline(iss, title, ',');
        std::getline(iss, word, ',');
        // next thing in line is starting number of available copies
        available = std::stoi(word);
        std::getline(iss, word, ',');
        // last thing in line is starting number of rented copies
        rented = std::stoi(word);
        // create a new DVD object to insert into binary tree
        DVD dvd(title, available, rented);
        // insert dvd into tree
        t.Insert(dvd);
        //std::cout << newNode->getPayload().getTitle() << ", " << newNode->getPayload().getAvailable() << ", " << newNode->getPayload().getRented()<< std::endl;
    }
}

void readTransactions(std::string filename, BinTree<DVD> &t)
{
    std::ifstream transactionInput;
    std::string line;
    std::string customerAction;
    std::string title;
    transactionInput.open(filename);
    while(getline(transactionInput, line))
    {
        std::istringstream iss(line);
        std::getline(iss, customerAction, ' ');
        std::getline(iss, title, ',');
        // create dummy DVD object to find if the movie exists in the binary tree
        DVD temp(title, 0, 0);
        DVD *foundDVD = t.Search(temp);
        if(customerAction == "add")
        {
            std::string word;
            std::getline(iss, word, ' ');
            int amount = std::stoi(word);
            // if it is nullptr, that means that the movie is not in the binary tree
            if(foundDVD == nullptr)
            {
                // create a new DVD object and insert it since it does not exist in the tree
                DVD dvd(title, amount, 0);
                t.Insert(dvd);
            }
            else
            {
                // add movie's available to the amount of copies being added in the transaction
                foundDVD->setAvailable(foundDVD->getAvailable() + amount);
            }
        }
        else if(customerAction == "rent")
        {
            // decrease movie's available copies by 1
            foundDVD->setAvailable(foundDVD->getAvailable() - 1);
            // increase movie's rented copies by 1
            foundDVD->setRented(foundDVD->getRented() + 1);
        }
        else if(customerAction == "return")
        {
            // increase movie's available copies by 1
            foundDVD->setAvailable(foundDVD->getAvailable() + 1);
            // decrease movie's rented copies by 1
            foundDVD->setRented(foundDVD->getRented() - 1);
        }
        else
        {
            std::string word;
            std::getline(iss, word, ',');
            int amount = std::stoi(word);
            foundDVD->setAvailable(foundDVD->getAvailable() - amount);
            // if there are no copies of the movie after removing copies, remove the movie from the binary tree
            if(foundDVD->getAvailable() + foundDVD->getRented() == 0)
            {
                t.Remove(*foundDVD);
            }
        }
    }
}
