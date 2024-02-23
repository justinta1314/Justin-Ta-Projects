#ifndef Auditorium_h
#define Auditorium_h

#include <iostream>
#include <fstream>
#include <string>
#include "Node.h"
#include <iomanip>
#include <cmath>

class Auditorium
{
    private:
        Node *first;
        int rows;
        int cols;
    public:
        Auditorium();
        Auditorium(std::string);
        void append(Seat, Node*&);
        void displayMenu();
        void reserveSeats(int, char, int, int, int);
        bool checkAvailability(int, char, int);
        static bool printFile;
        void displayReport();
        Seat bestAvailable(int);
        Node* getFirst() const;
        int getRows() const;
        int getColumns() const;
        ~Auditorium();
        bool getPrintFile();
        void setPrintFile(bool);
        
        friend std::ostream& operator<<(std::ostream&, Auditorium&);
};
#endif
