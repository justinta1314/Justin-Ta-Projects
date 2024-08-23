/*
Goal of Project: Using my implementation of a linked list to create 
                 a ticket reservation system for a movie theater
Test cases: 70/70
*/


#include <iostream>
#include <cctype>
#include <string>
#include "Auditorium.h"

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
    std::cout << "Please enter file name: ";
    std::string fileName;
    std::cin >> fileName;
    std::ifstream fileInput;
    fileInput.open(fileName);
    // check to make sure the fileStream is in a good state
    if(!fileInput)
    {
        std::cout << "Invalid File Name. Closing program...";
        fileInput.close();
        return 1;
    }
    // since the fileStream was in a good state, create auditorium using user's file name
    Auditorium a1(fileName);
    bool quit = 0;
    while(!quit)
    {
        a1.displayMenu();
        std::string selectionInput;
        std::cin >> selectionInput;
        if(validateInt(selectionInput)) // make sure that the selection input is an int
        {
            int selection = stoi(selectionInput);
            switch(selection)
            {
                case 1:
                {
                    std::cout << a1 << std::endl;
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
                    int totalTickets = numAdults + numChild + numSeniors;
                    if(a1.checkAvailability(row, startingSeat, totalTickets) == 1) // if the wanted seats are available
                    {
                        a1.reserveSeats(row, startingSeat, numAdults, numChild, numSeniors);
                        std::cout << "This is a confirmation of the seats you selected:" << std::endl;
                        std::cout << row << startingSeat << " - " << row << static_cast<char>(startingSeat + totalTickets - 1) << std::endl;
                        break;
                    }
                    else if(a1.bestAvailable(totalTickets).getColumn() != '\0')
                    {
                        /* if the user's wanted seats are not available, but there 
                        are seats in the auditorium that fit the user's criteria */
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
                                std::cout << a1.bestAvailable(totalTickets).getRow() << a1.bestAvailable(totalTickets).getColumn() << " - " << a1.bestAvailable(totalTickets).getRow() << static_cast<char>(a1.bestAvailable(totalTickets).getColumn() + totalTickets - 1) << std::endl;
                                a1.reserveSeats(a1.bestAvailable(totalTickets).getRow(), a1.bestAvailable(totalTickets).getColumn(), numAdults, numChild, numSeniors);
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
                case 2:
                {
                    // when the user decides to exit the main menu
                    std::cout << "Closing the program..." << std::endl;
                    a1.displayReport();
                    // create A1.txt file
                    std::ofstream theaterFile("A1.txt");
                    a1.setPrintFile(true);
                    // write the state of the auditorium to file
                    theaterFile << a1;
                    // close the file after use
                    theaterFile.close();
                    quit = true;
                    break;
                }
                default:
                    std::cout << "That is not a valid option. Please select again." << std::endl; // if the user doesn't select 1 or 2
                    break;
            }
        }
        else // if the user's input is not an integer
        {
            std::cout << "That is not a valid option. Please select again." << std::endl; 
        }
    }
    return 0;
}
