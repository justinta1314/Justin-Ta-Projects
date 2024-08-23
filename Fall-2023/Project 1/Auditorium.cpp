#include "Auditorium.h"

Auditorium::Auditorium()
{
    first = nullptr;
}

Auditorium::Auditorium(std::string inputFile)
{
    first = nullptr;
    rows = 0;
    cols = 0;
    std::ifstream fileInput;
    fileInput.open(inputFile);
    std::string curLine;
    // while you can get a line from the file
    while(std::getline(fileInput, curLine))
    {
        Node *curRow = nullptr;
        cols = static_cast<int>(curLine.length());
        char columnLetter = 'A';
        rows++;
        for(char c: curLine)
        {
            // create a new Seat for each char, which takes the current state of row and columnLetter as the row and seatColumn parameters
            Seat temp(rows, columnLetter, c);
            //add the seat to the end of the currentRow
            append(temp, curRow);
            //increment the columnLetter to the next letter
            columnLetter++;
        }
        if(first == nullptr)
        {
            first = curRow;
        }
        else
        {
            Node *temp = first;
            //go all the way down to the last row that was added
            while(temp->getDown() != nullptr)
            {
                temp = temp->getDown();
            }
            temp->setDown(curRow);
        }
    }
    // close the file after use
    fileInput.close();
}

void Auditorium::append(Seat s, Node *&currentRow)
{
    Node *newNode = new Node(s); // calls Node's overloaded constructor which sets the Node's seat to s
    //if the current row is empty
    if(currentRow == nullptr)
    {
        currentRow = newNode;
    }
    else
    {
        Node *cur = currentRow;
        while(cur->getNext() != nullptr)
        {
            cur = cur->getNext(); // go down the row until you reach the endd
        }
        cur->setNext(newNode); // set the next pointer to the new node
    }
}

void Auditorium::displayMenu()
{
    std::cout << "1. Reserve Seats" << std::endl << "2. Exit" << std::endl;
}

void Auditorium::reserveSeats(int row, char startingSeat, int numAdultTickets, int numChildTickets, int numSeniorTickets)
{
    Node *cur = first;
    //goes down to the row where seats are wanted
    for(int i = 0; i < row - 1; i++)
    {
        cur = cur->getDown();
    }
    // go through the row to the first seat that the user wants
    for(int i = 0; i < static_cast<int>(startingSeat) - 65; i++)
    {
        cur = cur->getNext();
    }
    for(int i = 0; i < numAdultTickets; i++)
    {
        cur->getSeat().setTicketType('A');
        cur = cur->getNext();
    }
    for(int i = 0; i < numChildTickets; i++)
    {
        cur->getSeat().setTicketType('C');
        cur = cur->getNext();
    }
    for(int i = 0; i < numSeniorTickets; i++)
    {
        cur->getSeat().setTicketType('S');
        cur = cur->getNext();
    }
}

bool Auditorium::checkAvailability(int row, char startingSeat, int numTickets)
{
    bool seatsEmpty = 1;
    Node *cur = first;
    for(int i = 0; i < row - 1; i++)
    {
        // go down to the wanted row
        cur = cur->getDown();
    }
    for(int i = 0; i < static_cast<int>(startingSeat) - 65; i++)
    {
        // go across the row to the starting seat
        cur = cur->getNext();
    }
    if(numTickets == 1) // if there is only one ticket wanted
    {
        if(cur->getSeat().getTicketType() != '.') // if the seat is not empty
        {
            seatsEmpty = false;
        }
    }
    else
    {
        // check the seats to see if there is a seat that is taken
        for(int i = 0; i < numTickets; i++)
        {
            // makes sure cur can't point to nullptr and try to get the ticket type there
            if(i != numTickets - 1 && cur->getNext() == nullptr)
            {
                seatsEmpty = false;
                break;
            }
            else if(cur->getSeat().getTicketType() != '.') // if the seat is not empty
            {
                seatsEmpty = false;
                break;
            }
            cur = cur->getNext();
        }
    }
    return seatsEmpty;
}

void Auditorium::displayReport()
{
    // set node pointers to the start of the auditorium
    Node *cur = first;
    Node *hold = first;
    int totalSeats = 0;
    int totalSold = 0;
    int adultTicketSold = 0;
    int childTicketSold = 0;
    int seniorTicketSold = 0;
    double totalSales = 0.0;
    for(int i = 0; i < rows; i++)
    {
        for(int o = 0; o < cols; o++)
        {
            totalSeats++; // increment total number of seats in auditorium
            if(cur->getSeat().getTicketType() != '.')
            {
                totalSold++; // increment number of seats that are not empty
                if(cur->getSeat().getTicketType() == 'A')
                {
                    adultTicketSold++; // increment number of adult seats
                    totalSales += 10; // each adult ticket is $10
                }
                if(cur->getSeat().getTicketType() == 'C')
                {
                    childTicketSold++; // increment number of child tickets
                    totalSales += 5; // each child ticket is $5
                }
                if(cur->getSeat().getTicketType() == 'S')
                {
                    seniorTicketSold++; // increment number of senior tickets
                    totalSales += 7.50; // each senior ticket is $7.50
                }
            }
            cur = cur->getNext(); // after each iteration, go to the next node
        }
        // after traversing the row, go down to the next row
        hold = hold->getDown();
        cur = hold;
    }
    
    std::cout << "Total Seats: " << totalSeats << std::endl;
    std::cout << "Total Tickets: " << totalSold << std::endl;
    std::cout << "Adult Tickets: " << adultTicketSold << std::endl;
    std::cout << "Child Tickets: " << childTicketSold << std::endl;
    std::cout << "Senior Tickets: " << seniorTicketSold << std::endl;
    std::cout << "Total Sales: $" << std::fixed << std::setprecision(2) << totalSales; // formats 
}

bool Auditorium::printFile = false;

Seat Auditorium::bestAvailable(int numTickets)
{
    bool seatsFound = false;
    double middleRow = rows / 2.0 + 0.5;
    double middleColumn = cols / 2.0 + 0.5;
    // distance formula with the first seat in the auditorium because that will be the furthest distance to the middle
    double bestDistance = sqrt(pow(0 - middleRow, 2) + pow(0 - middleColumn, 2));
    int bestRow = 0;
    char bestColumn = '\0';
    Node *currentRow = first;
    // create a seat using the default constructor
    Seat bestAvailableSeat;
    while(currentRow != nullptr)
    {
        // sets the current node to the start of the row
        Node *currentNode = currentRow;
        while(currentNode != nullptr)
        {
            // if the selection of seats starting with the current node is empty
            if(checkAvailability(currentNode->getSeat().getRow(), currentNode->getSeat().getColumn(), numTickets) == true)
            {
                seatsFound = true;
                double rowForDistance = currentNode->getSeat().getRow();
                double colForDistance = (currentNode->getSeat().getColumn() - 64) + (numTickets - 1) / 2.0;
                double distanceToMiddle = sqrt(pow(rowForDistance - middleRow, 2) + pow(colForDistance - middleColumn, 2));
                if(bestDistance > distanceToMiddle)
                {
                    bestDistance = distanceToMiddle;
                    bestRow = currentNode->getSeat().getRow();
                    bestColumn = currentNode->getSeat().getColumn();
                }
                else if(bestDistance == distanceToMiddle)
                {
                    // chooses the row closest to the middle
                    if(fabs(rowForDistance - middleRow) < fabs(bestRow - middleRow))
                    {
                        bestRow = currentNode->getSeat().getRow();
                        bestColumn = currentNode->getSeat().getColumn();
                    }
                    else if(fabs(rowForDistance - middleRow) == fabs(bestRow - middleRow))
                    {
                        // chooses the row with the smaller number if there are two rows closest to the middle
                        if(rowForDistance < bestRow)
                        {
                            bestRow = currentNode->getSeat().getRow();
                            bestColumn = currentNode->getSeat().getColumn();
                        }
                    }
                }
            }
            // goes to the next seat
            currentNode = currentNode->getNext();
        }
        // after the row is checked, go down to the next row
        currentRow = currentRow->getDown();
    }
    // if no seats are found, don't set any of the values to a value. bestAvailableSeat still holds default values
    if(seatsFound)
    {
        bestAvailableSeat.setRow(bestRow);
        bestAvailableSeat.setColumn(bestColumn);
    }
    return bestAvailableSeat;
}

// returns first node in the row
Node* Auditorium::getFirst() const
{
    return first;
}

// returns number of rows in auditorium
int Auditorium::getRows() const
{
    return rows;
}

// returns number of columns(number of seats in row) in auditorium
int Auditorium::getColumns() const
{
    return cols;
}

Auditorium::~Auditorium()
{
    Node *currentRow = first;
    while(currentRow)
    {
        Node *currentNode = currentRow;
        while(currentNode)
        {
            Node *temp = currentNode;
            currentNode = currentNode->getNext();
            delete temp;
        }
        currentRow = currentRow->getDown();
    }
}

bool Auditorium::getPrintFile()
{
    return printFile;
}

void Auditorium::setPrintFile(bool toFile)
{
    printFile = toFile;
}

std::ostream& operator<<(std::ostream &out, Auditorium &a)
{
    Node *cur = a.getFirst();
    Node *hold = a.getFirst();
    // if the << operator is being used to print the auditorium to the console
    if(!a.getPrintFile())
    {
        out << "  ";
        for(int i = 0; i < a.getColumns(); i++)
        {
            // adds column headers
            out << std::setw(5) << static_cast<char>(i + 65);
        }
        out << std::endl;
        for(int i = 0; i < a.getRows(); i++)
        {
            // adds row numbers
            out << i + 1 << " ";
            for(int o = 0; o < a.getColumns(); o++)
            {
                if(cur->getSeat().getTicketType() !='.')
                {
                    // if the seats are not empty, replace them with #. also formatted to keep text aligned
                    out << std::setw(5) << '#';
                    cur = cur->getNext();
                }
                else
                {
                    out << std::setw(5) << cur->getSeat().getTicketType();
                    cur = cur->getNext();
                }
            }
            // after going through the row, start a new line. hold is set to the start of the next row, and cur is set to hold
            out << std::endl;
            hold = hold->getDown();
            cur = hold;
        }
    }
    else
    {
        // for writing to the file
        for(int i = 0; i < a.getRows(); i++)
        {
            for(int o = 0; o < a.getColumns(); o++)
            {
                out << cur->getSeat().getTicketType();
                cur = cur->getNext();
            }
            // so that there is no extra white space
            if(i < a.getRows() - 1)
            {
                out << std::endl;
            }
            hold = hold->getDown();
            cur = hold;
        }
    }
    return out;
}
