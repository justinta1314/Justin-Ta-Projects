#ifndef Seat_h
#define Seat_h

#include <iostream>
class Seat
{
    private:
        int row;
        char column;
        char ticketType;
    public:
        Seat();
        Seat(int, char, char);
        void setRow(int);
        void setColumn(char);
        void setTicketType(char);
        int getRow() const;
        char getColumn() const;
        char getTicketType() const;
        
        friend std::ostream& operator<<(std::ostream&, const Seat&);
};
#endif
