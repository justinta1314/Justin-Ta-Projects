#ifndef Auditorium_h
#define Auditorium_h

#include <iostream>
#include <fstream>
#include <string>
#include "Node.h"
#include <iomanip>
#include <cmath>
#include <vector>

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
        void reserveSeats(int, char, int, int, int);
        bool checkAvailability(int, char, int);
        static bool printFile;
        void displayReport();
        Seat bestAvailable(int);
        Node* getFirst() const;
        int getRows() const;
        int getColumns() const;
        void unreserveSeat(Seat);
        void unreserveMultiple(std::vector<Seat>);
        ~Auditorium();
        bool getPrintFile();
        void setPrintFile(bool);
        int getOpenSeats();
        int getNumReserved();
        int getNumAdult();
        int getNumChild();
        int getNumSenior();
        
        friend std::ostream& operator<<(std::ostream&, Auditorium&);
};
#endif
