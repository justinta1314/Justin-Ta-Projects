/*
Goal of the Project:
Using what I implemented for Project 2, create a ticket reservation system for a movie theater.
There will be 3 auditoriums. There will also be a user database where each user has a login. 
Each customer can purchase tickets which will be saved as one of their orders.
Customers can update these orders; by adding tickets, removing tickets one by one, or cancelling the order.
The customer can also cancel the order by removing each ticket separately.
At the end of the program, print out a summary of all of the auditoriums and the money that was made.
The user database will be stored in an unordered_map or a hash table.
The auditoriums are implemented as linked lists which was my implementation.
*/

#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include "Auditorium.h"

struct Order
{
    int auditoriumNum;
    std::vector<Seat> seats;
    int numAdult;
    int numChild;
    int numSenior;
    Order(int audNum, int a, int c, int s)
    {
        auditoriumNum = audNum;
        numAdult = a;
        numChild = c;
        numSenior = s;
    }
    
    int getAuditoriumNum()
    {
        return auditoriumNum;
    }
    
    std::vector<Seat>& getSeats()
    {
        return seats;
    }
    
    int getNumAdult()
    {
        return numAdult;
    }
    
    int getNumChild()
    {
        return numChild;
    }
    
    int getNumSenior()
    {
        return numSenior;
    }
    
    double getPrice()
    {
        double price = 0;
        for(int i = 0; i < (int)seats.size(); i++)
        {
            // if the seat is reserved for an adult
            if(seats.at(i).getTicketType() == 'A')
            {
                price += 10;
            }
            // if the seat is reserved for a child
            else if(seats.at(i).getTicketType() == 'C')
            {
                price += 5;
            }
            // the seat is reserved for a senior
            else
            {
                price += 7.50;
            }
        }
        return price;
    }
    
    void addSeat(Seat s)
    {
        if(seats.empty())
        {
            // if there are no seats in the order yet, just add the first seat
            seats.push_back(s);
            return;
        }
        else
        {
            for(int i = 0; i < (int)seats.size(); i++)
            {
                std::vector<Seat>::iterator it;
                it = seats.begin();
                for(int j = 0; j < i; j++)
                {
                    ++it;
                }
                // if the row for the seat being inserted is lower than the seat in the order, insert the seat before
                if(s.getRow() < seats.at(i).getRow())
                {
                    seats.insert(it, s);
                    return;
                }
                // if the rows are the same, check the column and if column is lower, insert before
                else if(s.getRow() == seats.at(i).getRow())
                {
                    if(s.getColumn() < seats.at(i).getColumn())
                    {
                        seats.insert(it, s);
                        return;
                    }
                }
                else
                {
                    if(i == (int)seats.size() - 1)
                    {
                        seats.push_back(s);
                        return;
                    }
                    else
                    {
                        continue;
                    }
                }
            }
        }
        seats.push_back(s);
    }
    
    void removeSeat(Seat s)
    {
        for(int i = 0; i < (int)seats.size(); i++)
        {
            // if you find the seat in the order
            if(seats.at(i) == s)
            {
                std::vector<Seat>::iterator it;
                it = seats.begin();
                for(int j = 0; j < i; j++)
                {
                    ++it;
                }
                // decrement the correct total
                if(seats.at(i).getTicketType() == 'A')
                {
                    numAdult--;
                }
                else if(seats.at(i).getTicketType() == 'C')
                {
                    numChild--;
                }
                else
                {
                    numSenior--;
                }
                seats.erase(it);
            }
        }
    }
    
    bool contains(Seat s)
    {
        // check each seat in the vector
        for(int i = 0; i < (int)seats.size(); i++)
        {
            // if the seat in the vector has the same row number and seat column as Seat s, then the order contains the seat
            if(seats.at(i) == s)
            {
                return true;
            }
        }
        return false;
    }
    
    void append(Order o)
    {
        // insert each additional seat into the current order while finding its correct spot
        for(int i = 0; i < (int)o.getSeats().size(); i++)
        {
            this->addSeat(o.getSeats().at(i));
        }
        numAdult += o.getNumAdult();
        numChild += o.getNumChild();
        numSenior += o.getNumSenior();
    }
    
    void printSeats()
    {
        // go through the vector and print each seat in the vector from beginning to end
        for(int i = 0; i < (int)seats.size(); i++)
        {
            std::cout << seats.at(i).getRow() << seats.at(i).getColumn();
            if(i < (int)seats.size() - 1)
            {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
    }
};

struct Customer
{
    std::vector<Order> orders;
    std::string username;
    std::string password;
    Customer()
    {
        username = "";
        password = "";
    }
    Customer(std::string u, std::string p)
    {
        username = u;
        password = p;
    }
    
    std::string getUsername()
    {
        return username;
    }
    
    std::string getPassword()
    {
        return password;
    }
    
    std::vector<Order>& getOrders()
    {
        return orders;
    }
    
    void addOrder(Order o)
    {
        orders.push_back(o);
    }
    
    void printOrders()
    {
        if(orders.empty())
        {
            std::cout << "No orders" << std::endl;
        }
        else
        {
            for(int i = 0; i < (int)orders.size(); i++)
            {
                Order o = orders.at(i);
                // print the auditorium number for the order
                std::cout << "Auditorium " << o.getAuditoriumNum() << ", ";
                // print the seats that is in the order
                o.printSeats();
                // print out the number of adults, children, and seniors
                std::cout << o.getNumAdult();
                std::cout << " adult, ";
                std::cout << o.getNumChild() << " child, ";
                std::cout << o.getNumSenior();
                std::cout << " senior";
                std::cout << std::endl;
                // so that there isn't an extra '\n'
                if(i < (int)orders.size() - 1)
                {
                    std::cout << std::endl;
                }
            }
        }
    }
    
    // exact same function as printOrders, but includes the order # before each order is printed
    void printUpdateOrders()
    {
        if(orders.empty())
        {
            std::cout << "No orders" << std::endl;
        }
        else
        {
            for(int i = 0; i < (int)orders.size(); i++)
            {
                Order o = orders.at(i);
                std::cout << "Order #" << i + 1 << ": ";
                std::cout << "Auditorium " << o.getAuditoriumNum() << ", ";
                o.printSeats();
                std::cout << o.getNumAdult();
                std::cout << " adult, ";
                std::cout << o.getNumChild() << " child, ";
                std::cout << o.getNumSenior();
                std::cout << " senior";
                std::cout << std::endl;
                if(i < (int)orders.size())
                {
                    std::cout << std::endl;
                }
            }
        }
    }
    
    void printReceipt()
    {
        double totalPrice = 0;
        if(orders.empty())
        {
            std::cout << "No orders" << std::endl;
        }
        else
        {
            for(int i = 0; i < (int)orders.size(); i++)
            {
                // same functions as printOrders function
                Order o = orders.at(i);
                std::cout << "Auditorium " << o.getAuditoriumNum() << ", ";
                o.printSeats();
                std::cout << o.getNumAdult();
                std::cout << " adult, ";
                std::cout << o.getNumChild() << " child, ";
                std::cout << o.getNumSenior();
                std::cout << " senior";
                std::cout << std::endl;
                // show the total cost for the order
                std::cout << "Order Total: $" << std::fixed << std::setprecision(2) << o.getPrice();
                totalPrice += o.getPrice();
                std::cout << std::endl << std::endl;
            }
        }
        // show the total cost for all of the customer's orders
        std::cout << "Customer Total: $" << std::fixed << std::setprecision(2) << totalPrice;
        std::cout << std::endl << std::endl;
    }
    
    void removeOrder(int index)
    {
        orders.erase(orders.begin() + index);
    }
};

void fillCustomerData(std::unordered_map<std::string, Customer>&, std::string);

void displayCustomerMenu();

void displayAdminMenu();

void displayUpdateMenu();

void printReport(Auditorium&, Auditorium&, Auditorium&);

bool validateInt(std::string s)
{
    bool isInt = true;
    for(char c : s) // goes through each character in the string
    {
        if(!isdigit(c))
        {
            // if the character is not a dight (0-9)
            isInt = false;
            break;
        }
    }
    return isInt;
}

bool validateChar(std::string s)
{
    bool isChar = true;
    if(s.length() > 1)
    {
        /* the only inputs that aren't numeric should only be 1 
        letter, so the length of the string should only be 1 */
        isChar = false;
    }
    for(char c : s)
    {
        if(!isalpha(c)) // if the character is not part of the alphabet (A-Z, a-z)
        {
            isChar = false;
        }
    }
    return isChar;
}

int main()
{
    
    // Creating auditoriums and hashmap
    std::ifstream fileInput;
    fileInput.open("A1.txt");
    // check to make sure the fileStream is in a good state
    if(!fileInput)
    {
        std::cout << "Invalid Auditorium 1 file. Closing program...";
        fileInput.close();
        return 1;
    }
    // since the fileStream was in a good state, create auditorium using user's file name
    Auditorium a1("A1.txt");
    fileInput.close();
    fileInput.clear();
    fileInput.open("A2.txt");
    if(!fileInput)
    {
        std::cout << "Invalid Auditorium 2 file. Closing program...";
        fileInput.close();
        return 2;
    }
    Auditorium a2("A2.txt");
    fileInput.close();
    fileInput.clear();
    fileInput.open("A3.txt");
    if(!fileInput)
    {
        std::cout << "Invalid Auditorium 3 file. Closing program...";
        fileInput.close();
        return 3;
    }
    Auditorium a3("A3.txt");
    fileInput.close();
    fileInput.clear();
    fileInput.open("userdb.dat");
    if(!fileInput)
    {
        std::cout << "Invalid user database file. Closing program...";
        fileInput.close();
        return 4;
    }
    fileInput.close();
    std::unordered_map<std::string, Customer> users;
    fillCustomerData(users, "userdb.dat");
    
    
    bool quit = 0;
    while(!quit)
    {
        
        // Log In Procedure
        bool validPassword = false;
        int passwordAttempts = 0;
        std::string username;
        std::string password;
        std::cout << "Please enter your username: ";
        std::cin >> username;
        std::cout << "Please enter your password: ";
        std::cin >> password;
        passwordAttempts++;
        while(!validPassword)
        {
            if(users[username].getPassword() == password)
            {
                validPassword = true;
            }
            else
            {
                // making sure the user only gets 3 attempts to enter the password
                if(passwordAttempts < 3)
                {
                    std::cout << "Invalid password. Please try again." << std::endl;
                    std::cin >> password;
                    passwordAttempts++;
                }
                else
                {
                    break;
                }
            }
        }
        if(passwordAttempts == 3 && !validPassword)
        {
            // if the user does not enter the correct password in three tries, go back to prompting for username
            continue;
        }
        bool logout = false;
        while(!logout)
        {
            // create a customer pointer to the customer with the corresponding username
            Customer *user = &users[username];
            std::string choiceInput;
            // if the user logged in with admin credentials
            if(username == "admin")
            {
                displayAdminMenu();
                std::cin >> choiceInput;
                if(validateInt(choiceInput))
                {
                    int choice = std::stoi(choiceInput);
                    switch(choice)
                    {
                        // "Print Report" was selected
                        case 1:
                        {
                            printReport(a1, a2, a3);
                            break;
                        }
                        // "Log out" was selected
                        case 2:
                        {
                            std::cout << "Logging out." << std::endl;
                            logout = true;
                            break;
                        }
                        // "Exit" was selected
                        case 3:
                        {
                            std::cout << "Closing the program." << std::endl;
                            std::ofstream a1File("A1Final.txt");
                            a1.setPrintFile(true);
                            // Write the status of each auditorium to their corresponding files
                            a1File << a1;
                            a1File.close();
                            
                            std::ofstream a2File("A2Final.txt");
                            a2.setPrintFile(true);
                            a2File << a2;
                            a2File.close();
                            
                            std::ofstream a3File("A3Final.txt");
                            a3.setPrintFile(true);
                            a3File << a3;
                            a3File.close();
                            
                            logout = true;
                            quit = true;
                            break;
                        }
                        // Invalid option
                        default:
                        {
                            std::cout << "That is not a valid option. Please select again." << std::endl;
                            break;
                        }
                    }
                }
                // Invalid option
                else
                {
                    std::cout << "That is not a valid option. Please select again." << std::endl;
                }
            }
            else
            {
                displayCustomerMenu();
                std::cin >> choiceInput;
                if(validateInt(choiceInput))
                {
                    int choice = std::stoi(choiceInput);
                    std::cout << std::endl;
                    switch(choice)
                    {
                        // Reserve Seats was selected
                        case 1:
                        {
                            std::cout << "Please select an auditorium" << std::endl;
                            std::cout << "1. Auditorium 1\n2. Auditorium 2\n3. Auditorium 3\n";
                            std::string auditoriumInput;
                            std::cin >> auditoriumInput;
                            int auditoriumNum;
                            if(validateInt(auditoriumInput))
                            {
                                // store the auditorium number that the user wants
                                auditoriumNum = std::stoi(auditoriumInput);
                            }
                            else
                            {
                                while(!validateInt(auditoriumInput))
                                {
                                    std::cout << "That is not a valid option. Please try again." << std::endl;
                                    std::cin >> auditoriumInput;
                                }
                                auditoriumNum = std::stoi(auditoriumInput);
                            }
                            // check to make sure that the user's choice is within the correct range
                            while(auditoriumNum < 1 || auditoriumNum > 3)
                            {
                                std::cout << "That is not a valid option. Please try again." << std::endl;
                                std::cin >> auditoriumInput;
                                if(validateInt(auditoriumInput))
                                {
                                    auditoriumNum = std::stoi(auditoriumInput);
                                }
                                else
                                {
                                    while(!validateInt(auditoriumInput))
                                    {
                                        std::cout << "That is not a valid option. Please try again." << std::endl;
                                        std::cin >> auditoriumInput;
                                    }
                                    auditoriumNum = std::stoi(auditoriumInput);
                                }
                            }
                            // show the corresponding auditorium
                            if(auditoriumNum == 1)
                            {
                                std::cout << a1 << std::endl;
                            }
                            else if(auditoriumNum == 2)
                            {
                                std::cout << a2 << std::endl;
                            }
                            else
                            {
                                std::cout << a3 << std::endl;
                            }
                            // prompt the user for the row number
                            std::cout << "Please select a row number." << std::endl;
                            std::string rowInput;
                            std::cin >> rowInput;
                            int row;
                            // if user input is an integer
                            if(validateInt(rowInput))
                            {
                                // sets row to the integer that user inputs
                                row = stoi(rowInput);
                            }
                            else
                            {
                                while(!validateInt(rowInput))
                                {
                                    //while the input is not a int, it prompts for a new input. while loop validates the input after each pass
                                    std::cout << "Please enter an integer." << std::endl;
                                    std::cin >> rowInput;
                                }
                                // set the actual row number to the number that was in the input using string to int converter
                                row = stoi(rowInput);
                            }
                            // check to make sure the row number is within the correct range
                            if(auditoriumNum == 1)
                            {
                                while(row < 1 || row > a1.getRows()) // if the row is not an actual row
                                {
                                    // go through and get new row input, go through validating again
                                    std::cout << "Please select a valid row." << std::endl;
                                    std::cin >> rowInput;
                                    while(!validateInt(rowInput))
                                    {
                                        std::cout << "Please enter an integer." << std::endl;
                                        std::cin >> rowInput;
                                    }
                                    row = stoi(rowInput);
                                }
                            }
                            else if(auditoriumNum == 2)
                            {
                                while(row < 1 || row > a2.getRows()) // if the row is not an actual row
                                {
                                    // go through and get new row input, go through validating again
                                    std::cout << "Please select a valid row." << std::endl;
                                    std::cin >> rowInput;
                                    while(!validateInt(rowInput))
                                    {
                                        std::cout << "Please enter an integer." << std::endl;
                                        std::cin >> rowInput;
                                    }
                                    row = stoi(rowInput);
                                }
                            }
                            else
                            {
                                while(row < 1 || row > a3.getRows()) // if the row is not an actual row
                                {
                                    // go through and get new row input, go through validating again
                                    std::cout << "Please select a valid row." << std::endl;
                                    std::cin >> rowInput;
                                    while(!validateInt(rowInput))
                                    {
                                        std::cout << "Please enter an integer." << std::endl;
                                        std::cin >> rowInput;
                                    }
                                    row = stoi(rowInput);
                                }
                            }
                            // prompt the user for the starting seat
                            std::cout << "Please select your starting seat." << std::endl;
                            std::string startingSeatInput;
                            std::cin >> startingSeatInput;
                            char startingSeat;
                            if(validateChar(startingSeatInput)) // if the seat input is actually a letter
                            {
                                // set the starting seat to the uppercase version of the seat input
                                startingSeat = static_cast<char>(toupper(startingSeatInput.at(0)));
                            }
                            else
                            {
                                while(!validateChar(startingSeatInput))
                                {
                                    /*while the input is not an int, it prompts for a new 
                                    input. while loop validates the input after each pass*/
                                    std::cout << "Please enter a letter." << std::endl;
                                    std::cin >> startingSeatInput;
                                }
                                startingSeat = static_cast<char>(toupper(startingSeatInput.at(0)));
                            }
                            // if the seat letter the user inputs is not a actual seat letter in the auditorium
                            // all auditoriums will have the same number of columns
                            while(startingSeat < 'A' || startingSeat > 'A' + a1.getColumns())
                            {
                                // prompt the user for a new seat letter
                                std::cout << "Please select a valid seat letter." << std::endl;
                                std::cin >> startingSeatInput;
                                // if the new user input is not a char
                                while(!validateChar(startingSeatInput))
                                {
                                    // prompt user for new input, while loop validates new user input in each iteration
                                    std::cout << "Please enter a letter." << std::endl;
                                    std::cin >> startingSeatInput;
                                }
                                // set starting seat to the uppercase version of user input
                                startingSeat = static_cast<char>(toupper(startingSeatInput.at(0)));
                            }
                            // prompt the user for the number of adults, children, and seniors
                            std::cout << "How many adults are watching?" << std::endl;
                            std::string numAdultsInput;
                            std::cin >> numAdultsInput;
                            int numAdults;
                            // if the user input is an integer
                            if(validateInt(numAdultsInput))
                            {
                                // set numAdults to the number that the user inputs
                                numAdults = stoi(numAdultsInput);
                            }
                            else
                            {
                                // if the user input is not an integer
                                while(!validateInt(numAdultsInput))
                                {
                                    // prompt the user for new input. while loop validates new user input in each iteration
                                    std::cout << "Please enter an integer." << std::endl;
                                    std::cin >> numAdultsInput;
                                }
                                // set numAdults to the next valid input
                                numAdults = stoi(numAdultsInput);
                            }
                            // can't have a negative number of tickets
                            while(numAdults < 0)
                            {
                                // prompt user for new input
                                std::cout << "Please enter at least 0 tickets." << std::endl;
                                std::cin >> numAdultsInput;
                                // if the new input is not an int
                                while(!validateInt(numAdultsInput))
                                {
                                    // prompt user for new input. while loop validates new user input in each iteration
                                    std::cout << "Please enter an integer." << std::endl;
                                    std::cin >> numAdultsInput;
                                }
                                // set numAdults to the next valid input that is not negative
                                numAdults = stoi(numAdultsInput);
                            }
                            std::cout << "How many children are watching?" << std::endl;
                            std::string numChildInput;
                            std::cin >> numChildInput;
                            int numChild;
                            // if the user input is an integer
                            if(validateInt(numChildInput))
                            {
                                // set numChild to the to the number that the user inputs
                                numChild = stoi(numChildInput);
                            }
                            else
                            {
                                // if the user input is not an integer
                                while(!validateInt(numChildInput))
                                {
                                    // prompt user for new input. while loop validates input after each iteration
                                    std::cout << "Please enter an integer." << std::endl;
                                    std::cin >> numChildInput;
                                }
                                // sets numChild to the next valid integer input that is inputted
                                numChild = stoi(numChildInput);
                            }
                            // can't have negative number of tickets
                            while(numChild < 0)
                            {
                                // prompt the user for a new number of tickets
                                std::cout << "Please enter at least 0 tickets." << std::endl;
                                std::cin >> numChildInput;
                                // if the user input is not valid
                                while(!validateInt(numChildInput))
                                {
                                    // prompt the user for a new integer input
                                    std::cout << "Please enter an integer." << std::endl;
                                    std::cin >> numChildInput;
                                }
                                // sets numChild to the next integer input that the user gives
                                numChild = stoi(numChildInput);
                            }
                            std::cout << "And how many seniors are watching?" << std::endl;
                            std::string numSeniorsInput;
                            std::cin >> numSeniorsInput;
                            int numSeniors;
                            // if the user inputs an integer
                            if(validateInt(numSeniorsInput))
                            {
                                // sets numSeniors to the integer that the user inputs
                                numSeniors = stoi(numSeniorsInput);
                            }
                            else
                            {
                                // if the user input is not an integer
                                while(!validateInt(numSeniorsInput))
                                {
                                    // prompt the user for new input. while loop validates input after each iteration
                                    std::cout << "Please enter an integer." << std::endl;
                                    std::cin >> numSeniorsInput;
                                }
                                // sets numSeniors to the next integer input
                                numSeniors = stoi(numSeniorsInput);
                            }
                            // can't have a negative number of tickets. while loop checks after each iteration
                            while(numSeniors < 0)
                            {
                                // prompt user for new input
                                std::cout << "Please enter at least 0 tickets." << std::endl;
                                std::cin >> numSeniorsInput;
                                // if the user input is not an integer
                                while(!validateInt(numSeniorsInput))
                                {
                                    // prompt the user for new input. while loop validates input after each iteration
                                    std::cout << "Please enter an integer." << std::endl;
                                    std::cin >> numSeniorsInput;
                                }
                                // sets numSeniors to the next integer
                                numSeniors = stoi(numSeniorsInput);
                            }
                            // create a new order with the user's inputs
                            Order newOrder(auditoriumNum, numAdults, numChild, numSeniors);
                            int totalTickets = numAdults + numChild + numSeniors;
                            // check the availability of the seats in the corresponding auditorium
                            if(auditoriumNum == 1)
                            {
                                // if the wanted seats are available
                                if(a1.checkAvailability(row, startingSeat, totalTickets) == 1)
                                {
                                    // add each seat to the order
                                    for(int i = 0; i < numAdults; i++)
                                    {
                                        newOrder.addSeat(Seat(row, (char)(startingSeat + i), 'A'));
                                    }
                                    for(int i = 0; i < numChild; i++)
                                    {
                                        newOrder.addSeat(Seat(row, (char)(startingSeat + numAdults + i), 'C'));
                                    }
                                    for(int i = 0; i < numSeniors; i++)
                                    {
                                        newOrder.addSeat(Seat(row, (char)(startingSeat + numAdults + numChild + i), 'S'));
                                    }
                                    // add the order to the customer's orders
                                    user->addOrder(newOrder);
                                    a1.reserveSeats(row, startingSeat, numAdults, numChild, numSeniors);
                                    std::cout << "This is a confirmation of the seats you selected:" << std::endl;
                                    std::cout << row << startingSeat << " - " << row << static_cast<char>(startingSeat + totalTickets - 1) << std::endl;
                                    break;
                                }
                                else if(a1.bestAvailable(totalTickets).getColumn() != '\0')
                                {
                                    /* if the user's wanted seats are not available, but there 
                                    are seats in the auditorium that fit the user's criteria */
                                    Order newOrder(auditoriumNum, numAdults, numChild, numSeniors);
                                    std::cout << "We are sorry but 1 or more of those seats are taken. These are our best available seats in the theater: " << std::endl;
                                    std::cout << a1.bestAvailable(totalTickets).getRow() << a1.bestAvailable(totalTickets).getColumn() << " - " << a1.bestAvailable(totalTickets).getRow() << static_cast<char>(a1.bestAvailable(totalTickets).getColumn() + totalTickets - 1) << std::endl;
                                    std::cout << "Would you like these seats? Y/N" << std::endl;
                                    std::string yesNoInput;
                                    std::cin >> yesNoInput;
                                    char yesNo;
                                    // if the user input is a letter
                                    if(validateChar(yesNoInput))
                                    {
                                        // sets yesNo to the uppercase version of the user input
                                        yesNo = static_cast<char>(toupper(yesNoInput.at(0)));
                                    }
                                    else
                                    {
                                        // if the user input is not a single letter
                                        while(!validateChar(yesNoInput))
                                        {
                                            // prompt the user for new input. while loop validates input after each iteration
                                            std::cout << "Please enter an uppercase letter." << std::endl;
                                            std::cin >> yesNoInput;
                                        }
                                        // sets yesNo to uppercase version of user's input
                                        yesNo = static_cast<char>(toupper(yesNoInput.at(0)));
                                    }
                                    while(true)
                                    {
                                        // if user wants to reserve the best available seats
                                        if(yesNo == 'Y')
                                        {
                                            std::cout << "This is a confirmation of the seats you selected:" << std::endl;
                                            // add the seats to the order
                                            for(int i = 0; i < numAdults; i++)
                                            {
                                                newOrder.addSeat(Seat(a1.bestAvailable(totalTickets).getRow(), (char)(a1.bestAvailable(totalTickets).getColumn() + i), 'A'));
                                            }
                                            for(int i = 0; i < numChild; i++)
                                            {
                                                newOrder.addSeat(Seat(a1.bestAvailable(totalTickets).getRow(), (char)(a1.bestAvailable(totalTickets).getColumn() + numAdults + i), 'C'));
                                            }
                                            for(int i = 0; i < numSeniors; i++)
                                            {
                                                newOrder.addSeat(Seat(a1.bestAvailable(totalTickets).getRow(), (char)(a1.bestAvailable(totalTickets).getColumn() + numAdults + numChild + i), 'S'));
                                            }
                                            // show the confirmation of the user's new seats
                                            std::cout << a1.bestAvailable(totalTickets).getRow() << a1.bestAvailable(totalTickets).getColumn() << " - " << a1.bestAvailable(totalTickets).getRow() << static_cast<char>(a1.bestAvailable(totalTickets).getColumn() + totalTickets - 1) << std::endl;
                                            // reserve the seats
                                            a1.reserveSeats(a1.bestAvailable(totalTickets).getRow(), a1.bestAvailable(totalTickets).getColumn(), numAdults, numChild, numSeniors);
                                            // add the order to the customer's orders
                                            user->addOrder(newOrder);
                                            break;
                                        }
                                        else if(yesNo == 'N') // if the user does not want the best available seats
                                        {
                                            std::cout << "Ok. We are sorry for the inconvenience." << std::endl;
                                            break;
                                        }
                                        else
                                        {
                                            // if the user inputs something other than Y or N
                                            std::cout << "That is not a valid input. Please try again." << std::endl;
                                            std::cin >> yesNoInput;
                                            // if the user inputs something that is a letter
                                            if(validateChar(yesNoInput))
                                            {
                                                // sets yesNo to the letter that the user inputs
                                                yesNo = static_cast<char>(toupper(yesNoInput.at(0)));
                                            }
                                            else
                                            {
                                                // if the user does not input a single letter
                                                while(!validateChar(yesNoInput))
                                                {
                                                    /* if the user inputs something that is not a letter, prompt 
                                                    user for new input. while loop validates the new input */
                                                    std::cout << "Please enter a letter." << std::endl;
                                                    std::cin >> yesNoInput;
                                                }
                                                // set yesNo to uppercase version of the letter user inputs
                                                yesNo = static_cast<char>(toupper(yesNoInput.at(0)));
                                            }
                                        }
                                    }
                                    break;
                                }
                                else
                                {
                                    // if there are no seats in the auditorium that fit the user's criteria
                                    std::cout << "no seats available" << std::endl;
                                    break;
                                }
                            }
                            // same process as above
                            else if(auditoriumNum == 2)
                            {
                                if(a2.checkAvailability(row, startingSeat, totalTickets) == 1) // if the wanted seats are available
                                {
                                    for(int i = 0; i < numAdults; i++)
                                    {
                                        newOrder.addSeat(Seat(row, (char)(startingSeat + i), 'A'));
                                    }
                                    for(int i = 0; i < numChild; i++)
                                    {
                                        newOrder.addSeat(Seat(row, (char)(startingSeat + numAdults + i), 'C'));
                                    }
                                    for(int i = 0; i < numSeniors; i++)
                                    {
                                        newOrder.addSeat(Seat(row, (char)(startingSeat + numAdults + numChild + i), 'S'));
                                    }
                                    user->addOrder(newOrder);
                                    a2.reserveSeats(row, startingSeat, numAdults, numChild, numSeniors);
                                    std::cout << "This is a confirmation of the seats you selected:" << std::endl;
                                    std::cout << row << startingSeat << " - " << row << static_cast<char>(startingSeat + totalTickets - 1) << std::endl;
                                    break;
                                }
                                else if(a2.bestAvailable(totalTickets).getColumn() != '\0')
                                {
                                    /* if the user's wanted seats are not available, but there 
                                    are seats in the auditorium that fit the user's criteria */
                                    Order newOrder(2, numAdults, numChild, numSeniors);
                                    std::cout << "We are sorry but 1 or more of those seats are taken. These are our best available seats in the theater: " << std::endl;
                                    std::cout << a2.bestAvailable(totalTickets).getRow() << a2.bestAvailable(totalTickets).getColumn() << " - " << a2.bestAvailable(totalTickets).getRow() << static_cast<char>(a2.bestAvailable(totalTickets).getColumn() + totalTickets - 1) << std::endl;
                                    std::cout << "Would you like these seats? Y/N" << std::endl;
                                    std::string yesNoInput;
                                    std::cin >> yesNoInput;
                                    char yesNo;
                                    // if the user input is a letter
                                    if(validateChar(yesNoInput))
                                    {
                                        // sets yesNo to the uppercase version of the user input
                                        yesNo = static_cast<char>(toupper(yesNoInput.at(0)));
                                    }
                                    else
                                    {
                                        // if the user input is not a single letter
                                        while(!validateChar(yesNoInput))
                                        {
                                            // prompt the user for new input. while loop validates input after each iteration
                                            std::cout << "Please enter an uppercase letter." << std::endl;
                                            std::cin >> yesNoInput;
                                        }
                                        // sets yesNo to uppercase version of user's input
                                        yesNo = static_cast<char>(toupper(yesNoInput.at(0)));
                                    }
                                    while(true)
                                    {
                                        // if user wants to reserve the best available seats
                                        if(yesNo == 'Y')
                                        {
                                            std::cout << "This is a confirmation of the seats you selected:" << std::endl;
                                            for(int i = 0; i < numAdults; i++)
                                            {
                                                newOrder.addSeat(Seat(a2.bestAvailable(totalTickets).getRow(), (char)(a2.bestAvailable(totalTickets).getColumn() + i), 'A'));
                                            }
                                            for(int i = 0; i < numChild; i++)
                                            {
                                                newOrder.addSeat(Seat(a2.bestAvailable(totalTickets).getRow(), (char)(a2.bestAvailable(totalTickets).getColumn() + numAdults + i), 'C'));
                                            }
                                            for(int i = 0; i < numSeniors; i++)
                                            {
                                                newOrder.addSeat(Seat(a2.bestAvailable(totalTickets).getRow(), (char)(a2.bestAvailable(totalTickets).getColumn() + numAdults + numChild + i), 'S'));
                                            }
                                            std::cout << a2.bestAvailable(totalTickets).getRow() << a2.bestAvailable(totalTickets).getColumn() << " - " << a2.bestAvailable(totalTickets).getRow() << static_cast<char>(a2.bestAvailable(totalTickets).getColumn() + totalTickets - 1) << std::endl;
                                            a2.reserveSeats(a2.bestAvailable(totalTickets).getRow(), a2.bestAvailable(totalTickets).getColumn(), numAdults, numChild, numSeniors);
                                            user->addOrder(newOrder);
                                            break;
                                        }
                                        else if(yesNo == 'N') // if the user does not want the best available seats
                                        {
                                            std::cout << "Ok. We are sorry for the inconvenience." << std::endl;
                                            break;
                                        }
                                        else
                                        {
                                            // if the user inputs something other than Y or N
                                            std::cout << "That is not a valid input. Please try again." << std::endl;
                                            std::cin >> yesNoInput;
                                            // if the user inputs something that is a letter
                                            if(validateChar(yesNoInput))
                                            {
                                                // sets yesNo to the letter that the user inputs
                                                yesNo = static_cast<char>(toupper(yesNoInput.at(0)));
                                            }
                                            else
                                            {
                                                // if the user does not input a single letter
                                                while(!validateChar(yesNoInput))
                                                {
                                                    /* if the user inputs something that is not a letter, prompt 
                                                    user for new input. while loop validates the new input */
                                                    std::cout << "Please enter a letter." << std::endl;
                                                    std::cin >> yesNoInput;
                                                }
                                                // set yesNo to uppercase version of the letter user inputs
                                                yesNo = static_cast<char>(toupper(yesNoInput.at(0)));
                                            }
                                        }
                                    }
                                    break;
                                }
                                else
                                {
                                    // if there are no seats in the auditorium that fit the user's criteria
                                    std::cout << "no seats available" << std::endl;
                                    break;
                                }
                            }
                            // same process as for auditoriums 1 and 2
                            else
                            {
                                if(a3.checkAvailability(row, startingSeat, totalTickets) == 1) // if the wanted seats are available
                                {
                                    for(int i = 0; i < numAdults; i++)
                                    {
                                        newOrder.addSeat(Seat(row, (char)(startingSeat + i), 'A'));
                                    }
                                    for(int i = 0; i < numChild; i++)
                                    {
                                        newOrder.addSeat(Seat(row, (char)(startingSeat + numAdults + i), 'C'));
                                    }
                                    for(int i = 0; i < numSeniors; i++)
                                    {
                                        newOrder.addSeat(Seat(row, (char)(startingSeat + numAdults + numChild + i), 'S'));
                                    }
                                    user->addOrder(newOrder);
                                    a3.reserveSeats(row, startingSeat, numAdults, numChild, numSeniors);
                                    std::cout << "This is a confirmation of the seats you selected:" << std::endl;
                                    std::cout << row << startingSeat << " - " << row << static_cast<char>(startingSeat + totalTickets - 1) << std::endl;
                                    break;
                                }
                                else if(a3.bestAvailable(totalTickets).getColumn() != '\0')
                                {
                                    /* if the user's wanted seats are not available, but there 
                                    are seats in the auditorium that fit the user's criteria */
                                    Order newOrder(3, numAdults, numChild, numSeniors);
                                    std::cout << "We are sorry but 1 or more of those seats are taken. These are our best available seats in the theater: " << std::endl;
                                    std::cout << a3.bestAvailable(totalTickets).getRow() << a3.bestAvailable(totalTickets).getColumn() << " - " << a3.bestAvailable(totalTickets).getRow() << static_cast<char>(a3.bestAvailable(totalTickets).getColumn() + totalTickets - 1) << std::endl;
                                    std::cout << "Would you like these seats? Y/N" << std::endl;
                                    std::string yesNoInput;
                                    std::cin >> yesNoInput;
                                    char yesNo;
                                    // if the user input is a letter
                                    if(validateChar(yesNoInput))
                                    {
                                        // sets yesNo to the uppercase version of the user input
                                        yesNo = static_cast<char>(toupper(yesNoInput.at(0)));
                                    }
                                    else
                                    {
                                        // if the user input is not a single letter
                                        while(!validateChar(yesNoInput))
                                        {
                                            // prompt the user for new input. while loop validates input after each iteration
                                            std::cout << "Please enter an uppercase letter." << std::endl;
                                            std::cin >> yesNoInput;
                                        }
                                        // sets yesNo to uppercase version of user's input
                                        yesNo = static_cast<char>(toupper(yesNoInput.at(0)));
                                    }
                                    while(true)
                                    {
                                        // if user wants to reserve the best available seats
                                        if(yesNo == 'Y')
                                        {
                                            std::cout << "This is a confirmation of the seats you selected:" << std::endl;
                                            for(int i = 0; i < numAdults; i++)
                                            {
                                                newOrder.addSeat(Seat(a3.bestAvailable(totalTickets).getRow(), (char)(a3.bestAvailable(totalTickets).getColumn() + i), 'A'));
                                            }
                                            for(int i = 0; i < numChild; i++)
                                            {
                                                newOrder.addSeat(Seat(a3.bestAvailable(totalTickets).getRow(), (char)(a3.bestAvailable(totalTickets).getColumn() + numAdults + i), 'C'));
                                            }
                                            for(int i = 0; i < numSeniors; i++)
                                            {
                                                newOrder.addSeat(Seat(a3.bestAvailable(totalTickets).getRow(), (char)(a3.bestAvailable(totalTickets).getColumn() + numAdults + numChild + i), 'S'));
                                            }
                                            std::cout << a3.bestAvailable(totalTickets).getRow() << a3.bestAvailable(totalTickets).getColumn() << " - " << a3.bestAvailable(totalTickets).getRow() << static_cast<char>(a3.bestAvailable(totalTickets).getColumn() + totalTickets - 1) << std::endl;
                                            a3.reserveSeats(a3.bestAvailable(totalTickets).getRow(), a3.bestAvailable(totalTickets).getColumn(), numAdults, numChild, numSeniors);
                                            user->addOrder(newOrder);
                                            break;
                                        }
                                        else if(yesNo == 'N') // if the user does not want the best available seats
                                        {
                                            std::cout << "Ok. We are sorry for the inconvenience." << std::endl;
                                            break;
                                        }
                                        else
                                        {
                                            // if the user inputs something other than Y or N
                                            std::cout << "That is not a valid input. Please try again." << std::endl;
                                            std::cin >> yesNoInput;
                                            // if the user inputs something that is a letter
                                            if(validateChar(yesNoInput))
                                            {
                                                // sets yesNo to the letter that the user inputs
                                                yesNo = static_cast<char>(toupper(yesNoInput.at(0)));
                                            }
                                            else
                                            {
                                                // if the user does not input a single letter
                                                while(!validateChar(yesNoInput))
                                                {
                                                    /* if the user inputs something that is not a letter, prompt 
                                                    user for new input. while loop validates the new input */
                                                    std::cout << "Please enter a letter." << std::endl;
                                                    std::cin >> yesNoInput;
                                                }
                                                // set yesNo to uppercase version of the letter user inputs
                                                yesNo = static_cast<char>(toupper(yesNoInput.at(0)));
                                            }
                                        }
                                    }
                                    break;
                                }
                                else
                                {
                                    // if there are no seats in the auditorium that fit the user's criteria
                                    std::cout << "no seats available" << std::endl;
                                    break;
                                }
                            }
                            break;
                        }
                        
                        // View Orders was selected
                        case 2:
                        {
                            user->printOrders();
                            std::cout << std::endl;
                            break;
                        }
                        
                        // Update Order was selected
                        case 3:
                        {
                            bool orderUpdated = false;
                            user->printUpdateOrders();
                            if(user->getOrders().size() == 0)
                            {
                                break;
                            }
                            int orderSelection;
                            // checking to make sure the user has orders
                            if(user->getOrders().size() != 0)
                            {
                                std::cout << "Please select an order." << std::endl;
                                std::string orderSelectionInput;
                                std::cin >> orderSelectionInput;
                                // validate the user's choice for the order #
                                if(validateInt(orderSelectionInput))
                                {
                                    orderSelection = std::stoi(orderSelectionInput);
                                }
                                else
                                {
                                    while(!validateInt(orderSelectionInput))
                                    {
                                        std::cout << "That is not a valid option. Please try again." << std::endl;
                                        std::cin >> orderSelectionInput;
                                    }
                                    orderSelection = std::stoi(orderSelectionInput);
                                }
                                // if the user enters a number that is not in the range of their orders
                                while(orderSelection <= 0 || orderSelection > (int)user->getOrders().size())
                                {
                                    std::cout << "That is not a valid order. Please try again." << std::endl;
                                    std::cin >> orderSelectionInput;
                                    if(validateInt(orderSelectionInput))
                                    {
                                        orderSelection = std::stoi(orderSelectionInput);
                                    }
                                    else
                                    {
                                        while(!validateInt(orderSelectionInput))
                                        {
                                            std::cout << "That is not a valid option. Please try again." << std::endl;
                                            std::cin >> orderSelectionInput;
                                        }
                                        orderSelection = std::stoi(orderSelectionInput);
                                    }
                                }
                            }
                            // create order pointer to the order that the user picks
                            Order *currentOrder = &(user->getOrders().at(orderSelection - 1));
                            while(!orderUpdated)
                            {
                                displayUpdateMenu();
                                std::string updateOptionInput;
                                std::cin >> updateOptionInput;
                                int updateOption;
                                // validate the user's selection for update options
                                if(validateInt(updateOptionInput))
                                {
                                    updateOption = std::stoi(updateOptionInput);
                                }
                                else
                                {
                                    while(!validateInt(updateOptionInput))
                                    {
                                        std::cout << "That is not a valid option. Please try again." << std::endl;
                                        std::cin >> updateOptionInput;
                                    }
                                    updateOption = std::stoi(updateOptionInput);
                                }
                                int auditoriumRows;
                                int auditoriumColumns;
                                switch(updateOption)
                                {
                                    // Add tickets to order was selected
                                    case 1:
                                    {
                                        // display the corresponding auditorium
                                        if(currentOrder->getAuditoriumNum() == 1)
                                        {
                                            std::cout << a1 << std::endl;
                                            auditoriumRows = a1.getRows();
                                            auditoriumColumns = a1.getColumns();
                                        }
                                        else if(currentOrder->getAuditoriumNum() == 2)
                                        {
                                            std::cout << a2 << std::endl;
                                            auditoriumRows = a2.getRows();
                                            auditoriumColumns=a2.getColumns();
                                        }
                                        else
                                        {
                                            std::cout << a3 << std::endl;
                                            auditoriumRows = a3.getRows();
                                            auditoriumColumns = a3.getColumns();
                                        }
                                        std::cout << "Please select a row number." << std::endl;
                                        std::string rowInput;
                                        std::cin >> rowInput;
                                        int row;
                                        // if user input is an integer
                                        if(validateInt(rowInput))
                                        {
                                            // sets row to the integer that user inputs
                                            row = stoi(rowInput);
                                        }
                                        else
                                        {
                                            while(!validateInt(rowInput))
                                            {
                                                //while the input is not a int, it prompts for a new input. while loop validates the input after each pass
                                                std::cout << "Please enter an integer." << std::endl;
                                                std::cin >> rowInput;
                                            }
                                            // set the actual row number to the number that was in the input using string to int converter
                                            row = stoi(rowInput);
                                        }
                                        while(row < 1 || row >auditoriumRows) // if the row is not an actual row
                                        {
                                            // go through and get new row input, go through validating again
                                            std::cout << "Please select a valid row." << std::endl;
                                            std::cin >> rowInput;
                                            while(!validateInt(rowInput))
                                            {
                                                std::cout << "Please enter an integer." << std::endl;
                                                std::cin >> rowInput;
                                            }
                                            row = stoi(rowInput);
                                        }
                                        std::cout << "Please select your starting seat." << std::endl;
                                        std::string startingSeatInput;
                                        std::cin >> startingSeatInput;
                                        char startingSeat;
                                        if(validateChar(startingSeatInput)) // if the seat input is actually a letter
                                        {
                                            // set the starting seat to the uppercase version of the seat input
                                            startingSeat = static_cast<char>(toupper(startingSeatInput.at(0)));
                                        }
                                        else
                                        {
                                            while(!validateChar(startingSeatInput))
                                            {
                                                /*while the input is not an int, it prompts for a new 
                                                input. while loop validates the input after each pass*/
                                                std::cout << "Please enter a letter." << std::endl;
                                                std::cin >> startingSeatInput;
                                            }
                                            startingSeat = static_cast<char>(toupper(startingSeatInput.at(0)));
                                        }
                                        // if the seat letter the user inputs is not a actual seat letter in the auditorium
                                        while(startingSeat < 'A' || startingSeat > 'A' + auditoriumColumns)
                                        {
                                            // prompt the user for a new seat letter
                                            std::cout << "Please select a valid seat letter." << std::endl;
                                            std::cin >> startingSeatInput;
                                            // if the new user input is not a char
                                            while(!validateChar(startingSeatInput))
                                            {
                                                // prompt user for new input, while loop validates new user input in each iteration
                                                std::cout << "Please enter a letter." << std::endl;
                                                std::cin >> startingSeatInput;
                                            }
                                            // set starting seat to the uppercase version of user input
                                            startingSeat = static_cast<char>(toupper(startingSeatInput.at(0)));
                                        }
                                        std::cout << "How many adults are watching?" << std::endl;
                                        std::string numAdultsInput;
                                        std::cin >> numAdultsInput;
                                        int numAdults;
                                        // if the user input is an integer
                                        if(validateInt(numAdultsInput))
                                        {
                                            // set numAdults to the number that the user inputs
                                            numAdults = stoi(numAdultsInput);
                                        }
                                        else
                                        {
                                            // if the user input is not an integer
                                            while(!validateInt(numAdultsInput))
                                            {
                                                // prompt the user for new input. while loop validates new user input in each iteration
                                                std::cout << "Please enter an integer." << std::endl;
                                                std::cin >> numAdultsInput;
                                            }
                                            // set numAdults to the next valid input
                                            numAdults = stoi(numAdultsInput);
                                        }
                                        // can't have a negative number of tickets
                                        while(numAdults < 0)
                                        {
                                            // prompt user for new input
                                            std::cout << "Please enter at least 0 tickets." << std::endl;
                                            std::cin >> numAdultsInput;
                                            // if the new input is not an int
                                            while(!validateInt(numAdultsInput))
                                            {
                                                // prompt user for new input. while loop validates new user input in each iteration
                                                std::cout << "Please enter an integer." << std::endl;
                                                std::cin >> numAdultsInput;
                                            }
                                            // set numAdults to the next valid input that is not negative
                                            numAdults = stoi(numAdultsInput);
                                        }
                                        std::cout << "How many children are watching?" << std::endl;
                                        std::string numChildInput;
                                        std::cin >> numChildInput;
                                        int numChild;
                                        // if the user input is an integer
                                        if(validateInt(numChildInput))
                                        {
                                            // set numChild to the to the number that the user inputs
                                            numChild = stoi(numChildInput);
                                        }
                                        else
                                        {
                                            // if the user input is not an integer
                                            while(!validateInt(numChildInput))
                                            {
                                                // prompt user for new input. while loop validates input after each iteration
                                                std::cout << "Please enter an integer." << std::endl;
                                                std::cin >> numChildInput;
                                            }
                                            // sets numChild to the next valid integer input that is inputted
                                            numChild = stoi(numChildInput);
                                        }
                                        // can't have negative number of tickets
                                        while(numChild < 0)
                                        {
                                            // prompt the user for a new number of tickets
                                            std::cout << "Please enter at least 0 tickets." << std::endl;
                                            std::cin >> numChildInput;
                                            // if the user input is not valid
                                            while(!validateInt(numChildInput))
                                            {
                                                // prompt the user for a new integer input
                                                std::cout << "Please enter an integer." << std::endl;
                                                std::cin >> numChildInput;
                                            }
                                            // sets numChild to the next integer input that the user gives
                                            numChild = stoi(numChildInput);
                                        }
                                        std::cout << "And how many seniors are watching?" << std::endl;
                                        std::string numSeniorsInput;
                                        std::cin >> numSeniorsInput;
                                        int numSeniors;
                                        // if the user inputs an integer
                                        if(validateInt(numSeniorsInput))
                                        {
                                            // sets numSeniors to the integer that the user inputs
                                            numSeniors = stoi(numSeniorsInput);
                                        }
                                        else
                                        {
                                            // if the user input is not an integer
                                            while(!validateInt(numSeniorsInput))
                                            {
                                                // prompt the user for new input. while loop validates input after each iteration
                                                std::cout << "Please enter an integer." << std::endl;
                                                std::cin >> numSeniorsInput;
                                            }
                                            // sets numSeniors to the next integer input
                                            numSeniors = stoi(numSeniorsInput);
                                        }
                                        // can't have a negative number of tickets. while loop checks after each iteration
                                        while(numSeniors < 0)
                                        {
                                            // prompt user for new input
                                            std::cout << "Please enter at least 0 tickets." << std::endl;
                                            std::cin >> numSeniorsInput;
                                            // if the user input is not an integer
                                            while(!validateInt(numSeniorsInput))
                                            {
                                                // prompt the user for new input. while loop validates input after each iteration
                                                std::cout << "Please enter an integer." << std::endl;
                                                std::cin >> numSeniorsInput;
                                            }
                                            // sets numSeniors to the next integer
                                            numSeniors = stoi(numSeniorsInput);
                                        }
                                        // create a new order with the seats that are wanted to be added
                                        Order newOrder(currentOrder->getAuditoriumNum(), numAdults, numChild, numSeniors);
                                        int totalTickets = numAdults + numChild + numSeniors;
                                        // if the order is in auditorium 1
                                        if(currentOrder->getAuditoriumNum() == 1)
                                        {
                                            // if the seats are available, then reserve
                                            if(a1.checkAvailability(row, startingSeat, totalTickets) == 1) // if the wanted seats are available
                                            {
                                                // add the seats to the new order
                                                for(int i = 0; i < numAdults; i++)
                                                {
                                                    newOrder.addSeat(Seat(row, (char)(startingSeat + i), 'A'));
                                                }
                                                for(int i = 0; i < numChild; i++)
                                                {
                                                    newOrder.addSeat(Seat(row, (char)(startingSeat + numAdults + i), 'C'));
                                                }
                                                for(int i = 0; i < numSeniors; i++)
                                                {
                                                    newOrder.addSeat(Seat(row, (char)(startingSeat + numAdults + numChild + i), 'S'));
                                                }
                                                // add the seats from the new order to the current order
                                                currentOrder->append(newOrder);
                                                // reserve the seats that the user wants to add
                                                a1.reserveSeats(row, startingSeat, numAdults, numChild, numSeniors);
                                                std::cout << "This is a confirmation of the seats you selected:" << std::endl;
                                                std::cout << row << startingSeat << " - " << row << static_cast<char>(startingSeat + totalTickets - 1) << std::endl;
                                                orderUpdated = true;
                                                break;
                                            }
                                            // don't offer the best available
                                            else
                                            {
                                                std::cout << "The selected seats are not available." << std::endl;
                                            }
                                        }
                                        // same process as for auditorium 1
                                        else if(currentOrder->getAuditoriumNum() == 2)
                                        {
                                            if(a2.checkAvailability(row, startingSeat, totalTickets) == 1) // if the wanted seats are available
                                            {
                                                for(int i = 0; i < numAdults; i++)
                                                {
                                                    newOrder.addSeat(Seat(row, (char)(startingSeat + i), 'A'));
                                                }
                                                for(int i = 0; i < numChild; i++)
                                                {
                                                    newOrder.addSeat(Seat(row, (char)(startingSeat + numAdults + i), 'C'));
                                                }
                                                for(int i = 0; i < numSeniors; i++)
                                                {
                                                    newOrder.addSeat(Seat(row, (char)(startingSeat + numAdults + numChild + i), 'S'));
                                                }
                                                currentOrder->append(newOrder);
                                                a2.reserveSeats(row, startingSeat, numAdults, numChild, numSeniors);
                                                std::cout << "This is a confirmation of the seats you selected:" << std::endl;
                                                std::cout << row << startingSeat << " - " << row << static_cast<char>(startingSeat + totalTickets - 1) << std::endl;
                                                orderUpdated = true;
                                                break;
                                            }
                                            else
                                            {
                                                std::cout << "The selected seats are not available." << std::endl;
                                            }
                                        }
                                        // same process as for auditoriums 1 and 2
                                        else
                                        {
                                            if(a3.checkAvailability(row, startingSeat, totalTickets) == 1) // if the wanted seats are available
                                            {
                                                for(int i = 0; i < numAdults; i++)
                                                {
                                                    newOrder.addSeat(Seat(row, (char)(startingSeat + i), 'A'));
                                                }
                                                for(int i = 0; i < numChild; i++)
                                                {
                                                    newOrder.addSeat(Seat(row, (char)(startingSeat + numAdults + i), 'C'));
                                                }
                                                for(int i = 0; i < numSeniors; i++)
                                                {
                                                    newOrder.addSeat(Seat(row, (char)(startingSeat + numAdults + numChild + i), 'S'));
                                                }
                                                currentOrder->append(newOrder);
                                                a3.reserveSeats(row, startingSeat, numAdults, numChild, numSeniors);
                                                std::cout << "This is a confirmation of the seats you selected:" << std::endl;
                                                std::cout << row << startingSeat << " - " << row << static_cast<char>(startingSeat + totalTickets - 1) << std::endl;
                                                orderUpdated = true;
                                                break;
                                            }
                                            else
                                            {
                                                std::cout << "The selected seats are not available." << std::endl;
                                            }
                                        }
                                        break;
                                    }
                                    
                                    case 2: // Delete ticket from order was selected
                                    {
                                        std::cout << "What row is the seat that you would like to remove in?" << std::endl;
                                        std::string rowRemoveInput;
                                        std::cin >> rowRemoveInput;
                                        int rowRemove;
                                        // checking to make sure the user's input is an integer
                                        if(validateInt(rowRemoveInput))
                                        {
                                            rowRemove = std::stoi(rowRemoveInput);
                                        }
                                        else
                                        {
                                            while(!validateInt(rowRemoveInput))
                                            {
                                                std::cout << "Please enter an integer." << std::endl;
                                                std::cin >> rowRemoveInput;
                                            }
                                            rowRemove = std::stoi(rowRemoveInput);
                                        }
                                        if(currentOrder->getAuditoriumNum() == 1)
                                        {
                                            auditoriumRows = a1.getRows();
                                            auditoriumColumns = a1.getColumns();
                                        }
                                        else if(currentOrder->getAuditoriumNum() == 2)
                                        {
                                            auditoriumRows = a2.getRows();
                                            auditoriumColumns = a2.getColumns();
                                        }
                                        else
                                        {
                                            auditoriumRows = a3.getRows();
                                            auditoriumColumns = a3.getColumns();
                                        }
                                        // check to make sure the user's input is a valid row
                                        while(rowRemove < 1 || rowRemove > auditoriumRows)
                                        {
                                            std::cout << "That is not a valid row. Please select again." << std::endl;
                                            std::cin >> rowRemoveInput;
                                            if(validateInt(rowRemoveInput))
                                            {
                                                rowRemove = std::stoi(rowRemoveInput);
                                            }
                                            else
                                            {
                                                while(!validateInt(rowRemoveInput))
                                                {
                                                    std::cout << "Please enter an integer." << std::endl;
                                                    std::cin >> rowRemoveInput;
                                                }
                                                rowRemove = std::stoi(rowRemoveInput);
                                            }
                                        }
                                        std::cout << "What is the seat letter of the seat that you would like to remove?" << std::endl;
                                        std::string columnRemoveInput;
                                        std::cin >> columnRemoveInput;
                                        char columnRemove;
                                        // make sure the user inputs a valid character
                                        if(validateChar(columnRemoveInput))
                                        {
                                            columnRemove = (char)(toupper(columnRemoveInput.at(0)));
                                        }
                                        else
                                        {
                                            while(!validateChar(columnRemoveInput))
                                            {
                                                std::cout << "Please enter a character." << std::endl;
                                                std::cin >> columnRemoveInput;
                                            }
                                            columnRemove = (char)(toupper(columnRemoveInput.at(0)));
                                        }
                                        // check to see if the user's input is within the correct range
                                        while(columnRemove < 'A' || columnRemove > 'A' + auditoriumColumns)
                                        {
                                            std::cout << "That is not a valid seat letter. PLease try again." << std::endl;
                                            std::cin >> columnRemoveInput;
                                            if(validateChar(columnRemoveInput))
                                            {
                                                columnRemove = (char)(toupper(columnRemoveInput.at(0)));
                                            }
                                            else
                                            {
                                                while(!validateChar(columnRemoveInput))
                                                {
                                                    std::cout << "Please enter a character." << std::endl;
                                                    std::cin >> columnRemoveInput;
                                                }
                                                columnRemove = (char)(toupper(columnRemoveInput.at(0)));
                                            }
                                        }
                                        while(true)
                                        {
                                            // if there are no more seats in the order, remove the order
                                            if(currentOrder->getSeats().size() == 0)
                                            {
                                                std::cout << "There are no more seats in this order. Removing order." << std::endl;
                                                user->removeOrder(orderSelection - 1);
                                                break;
                                            }
                                            else
                                            {
                                                // if the order contains the seat that the user wants to remove
                                                if(currentOrder->contains(Seat(rowRemove, columnRemove, '\0')))
                                                {
                                                    // remove the seat from the order
                                                    currentOrder->removeSeat((Seat(rowRemove, columnRemove, '\0')));
                                                    // unreserve the seat from the correct auditorium
                                                    if(currentOrder->getAuditoriumNum() == 1)
                                                    {
                                                        a1.unreserveSeat(Seat(rowRemove, columnRemove, '\0'));
                                                    }
                                                    else if(currentOrder->getAuditoriumNum() == 2)
                                                    {
                                                        a2.unreserveSeat(Seat(rowRemove, columnRemove, '\0'));
                                                    }
                                                    else
                                                    {
                                                        a3.unreserveSeat(Seat(rowRemove, columnRemove, '\0'));
                                                    }
                                                    orderUpdated = true;
                                                    std::cout << "Seat removed from your order." << std::endl;
                                                }
                                                // if the user wants to remove a seat that is not in their order
                                                else
                                                {
                                                    std::cout << "That is not one of the seats in your order." << std::endl;
                                                    break;
                                                }
                                            }
                                        }
                                        break;
                                    }
                                    
                                    // Cancel order was selected
                                    case 3:
                                    {
                                        // while the order is not empty
                                        while(!currentOrder->getSeats().empty())
                                        {
                                            // unreserve the first seat in the order
                                            if(currentOrder->getAuditoriumNum() == 1)
                                            {
                                                a1.unreserveSeat(Seat(currentOrder->getSeats().at(0).getRow(), currentOrder->getSeats().at(0).getColumn(), '\0'));
                                            }
                                            else if(currentOrder->getAuditoriumNum() == 2)
                                            {
                                                a2.unreserveSeat(Seat(currentOrder->getSeats().at(0).getRow(), currentOrder->getSeats().at(0).getColumn(), '\0'));
                                            }
                                            else
                                            {
                                                a3.unreserveSeat(Seat(currentOrder->getSeats().at(0).getRow(), currentOrder->getSeats().at(0).getColumn(), '\0'));
                                            }
                                            // remove the seat from the order
                                            currentOrder->removeSeat(currentOrder->getSeats().at(0));
                                        }
                                        // remove the order
                                        user->removeOrder(orderSelection - 1);
                                        std::cout << "Order cancelled." << std::endl;
                                        orderUpdated = true;
                                        break;
                                    }
                                    
                                    // Invalid option
                                    default:
                                    {
                                        std::cout << "That is not a valid option. Please try again." << std::endl;
                                        break;
                                    }
                                }
                            }
                            break;
                        }
                        
                        // Display Receipt was selected
                        case 4:
                        {
                            user->printReceipt();
                            break;
                        }
                        
                        // Log Out was selected
                        case 5:
                        {
                            std::cout << "Logging out." << std::endl;
                            logout = true;
                            break;
                        }
                        
                        // User input was invalid
                        default:
                        {
                            std::cout << "That is not a valid option. Please select again." << std::endl;
                            break;
                        }
                    }
                }
                else
                {
                    std::cout << "That is not a valid option. Please select again." << std::endl;
                }
            }
        }
    }
    return 0;
}


void fillCustomerData(std::unordered_map<std::string, Customer> &map, std::string filename)
{
    std::ifstream fileInput;
    fileInput.open(filename);
    std::string line;
    while(getline(fileInput, line))
    {
        std::istringstream iss(line);
        std::string username;
        std::string password;
        // get the username and password from the userdb.dat file
        getline(iss, username, ' ');
        getline(iss, password, ' ');
        // insert a customer object using the username as the key into the unordered_map
        map.emplace(username, Customer(username, password));
    }
}

void displayUpdateMenu()
{
    std::cout << "1. Add tickets to order\n2. Delete tickets from order\n3. Cancel order\n";
}

void displayAdminMenu()
{
    std::cout << "1. Print Report\n2. Logout\n3. Exit\n";
}

void displayCustomerMenu()
{
    std::cout << "1. Reserve Seats\n2. View Orders\n3. Update Order\n4. Display Receipt\n5. Log Out\n";
}

void printReport(Auditorium &a1, Auditorium &a2, Auditorium &a3)
{
    // get the values of open, reserved, adult, child, and senior seats from each auditorium
    int a1Open = a1.getOpenSeats();
    int a1Reserved = a1.getNumReserved();
    int a1Adult = a1.getNumAdult();
    int a1Child = a1.getNumChild();
    int a1Senior = a1.getNumSenior();
    // get the total prices for the number of adults, children, seniors. also gets the total price of all tickets
    double a1AdultPrice = a1Adult * 10;
    double a1ChildPrice = a1Child * 5;
    double a1SeniorPrice = a1Senior * 7.50;
    double a1TotalPrice = a1AdultPrice + a1ChildPrice + a1SeniorPrice;
    
    int a2Open = a2.getOpenSeats();
    int a2Reserved = a2.getNumReserved();
    int a2Adult = a2.getNumAdult();
    int a2Child = a2.getNumChild();
    int a2Senior = a2.getNumSenior();
    double a2AdultPrice = a2Adult * 10;
    double a2ChildPrice = a2Child * 5;
    double a2SeniorPrice = a2Senior * 7.50;
    double a2TotalPrice = a2AdultPrice + a2ChildPrice + a2SeniorPrice;
    
    int a3Open = a3.getOpenSeats();
    int a3Reserved = a3.getNumReserved();
    int a3Adult = a3.getNumAdult();
    int a3Child = a3.getNumChild();
    int a3Senior = a3.getNumSenior();
    double a3AdultPrice = a3Adult * 10;
    double a3ChildPrice = a3Child * 5;
    double a3SeniorPrice = a3Senior * 7.50;
    double a3TotalPrice = a3AdultPrice + a3ChildPrice + a3SeniorPrice;
    
    // display each auditoriums information, and display the total at the end
    std::cout << "Auditorium 1\t" << a1Open << "\t" << a1Reserved << "\t" << a1Adult << "\t" << a1Child << "\t" << a1Senior << "\t$" << std::fixed << std::setprecision(2) << a1TotalPrice << std::endl;
    std::cout << "Auditorium 2\t" << a2Open << "\t" << a2Reserved << "\t" << a2Adult << "\t" << a2Child << "\t" << a2Senior << "\t$" << std::fixed << std::setprecision(2) << a2TotalPrice << std::endl;
    std::cout << "Auditorium 3\t" << a3Open << "\t" << a3Reserved << "\t" << a3Adult << "\t" << a3Child << "\t" << a3Senior << "\t$" << std::fixed << std::setprecision(2) << a3TotalPrice << std::endl;
    std::cout << "Total\t\t" << (a1Open + a2Open + a3Open) << "\t" << (a1Reserved + a2Reserved + a3Reserved) << "\t" << (a1Adult + a2Adult + a3Adult) << "\t" << (a1Child + a2Child + a3Child) 
    << "\t" << (a1Senior + a2Senior + a3Senior) << "\t$" << std::fixed << std::setprecision(2) << (a1TotalPrice + a2TotalPrice + a3TotalPrice) << std::endl;
}

