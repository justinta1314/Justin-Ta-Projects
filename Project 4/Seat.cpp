#include "Seat.h"

// default constructor, which sets everything to default values
Seat::Seat()
{
    row = 0;
    column = '\0';
    ticketType = '\0';
}

// sets row, column letter, and ticket type in overloaded constructor
Seat::Seat(int r, char c, char t)
{
    row = r;
    column = c;
    ticketType = t;
}

// sets row number to r
void Seat::setRow(int r)
{
    row = r;
}

// sets column letter to c
void Seat::setColumn(char c)
{
    column = c;
}

// sets ticket type to t
void Seat::setTicketType(char t)
{
    ticketType = t;
}

// returns the row number of the seat
int Seat::getRow() const
{
    return row;
}

// returns the column letter of the seat
char Seat::getColumn() const
{
    return column;
}

// return the ticket type of the seat
char Seat::getTicketType() const
{
    return ticketType;
}

bool Seat::operator==(const Seat& obj)
{
    if(this->row == obj.row && this->column == obj.column)
    {
        return true;
    }
    return false;
}

std::ostream& operator<<(std::ostream &out, const Seat& obj)
{
    out << obj.getTicketType();
    return out;
}
