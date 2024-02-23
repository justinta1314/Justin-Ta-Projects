/*
Goal of Project: 
To create a customer reward program with three tiers; regular, gold, and platinum.
If customers spend enough money, they can be promoted to a higher tier.
Gold customers get a discount that increases as they spend more money.
Platinum customers can earn bonus bucks for every 5 dollars that they spend.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <iomanip>
#include "Customer.h"
#include "Gold.h"
#include "Platinum.h"

void fillRegularArray(std::string fileInput, Customer *array[], int numCustomers);

void fillPreferredArray(std::string fileInput, Customer *array[], int numCustomers);

double calculatePrice(std::string size, std::string drinkType, double sqInchPrice, int numDrinks);

Customer** removeFromRegular(Customer *oldArray[], int oldNumRegular, int indexOfCustomer);

Customer** addCustomer(Customer *oldArray[], int oldNumPreferred, Customer *newCustomer);

std::string regularToFile(Customer *regArray[], int numRegular);

std::string preferredToFile(Customer *prefArray[], int numPreferred);

int calculateBonusBucks(double amountSpent, int numBonusBucks);

int findRegularIndex(Customer *regArray[], int numRegular, std::string id);

int findPreferredIndex(Customer *prefArray[], int numPreferred, std::string id);

int main()
{
    std::cout << "Please enter the regular customer file name: " << std::endl;
    std::string regCustomerFile;
    std::cin >> regCustomerFile;
    std::ifstream regFileInput;
    regFileInput.open(regCustomerFile);
    // if the regular customer file is invalid
    if(!regFileInput)
    {
        std::cout << "Invalid file name. Closing Program..." << std::endl;
        regFileInput.close();
        return 1;
    }
    std::string line;
    int lineCount = 0;
    // counts the number of lines in the file, this will give us the size of the array to start
    while(getline(regFileInput, line))
    {
        lineCount++;
    }
    int numRegCustomers = lineCount;
    Customer **regCustomers = new Customer*[numRegCustomers];
    // fill the regular array using the file
    fillRegularArray(regCustomerFile, regCustomers, numRegCustomers);
    std::cout << "Please enter the preferred customer file name: " << std::endl;
    std::string prefCustomerFile;
    std::cin >> prefCustomerFile;
    std::ifstream prefFileInput;
    prefFileInput.open(prefCustomerFile);
    lineCount = 0;
    // if the file is in a good state, check to make sure it's not empty
    if(prefFileInput)
    {
        while(getline(prefFileInput, line))
        {
            if(line != "")
            {
                lineCount++;
            }
        }
    }
    else
    {
        prefFileInput.close();
    }
    int numPrefCustomers = 0;
    bool prefArrayMade = false;
    // start as nullptr in case the file does not exist or is empty
    Customer **prefCustomers = nullptr;
    // if the file exists and the file is not empty
    if(lineCount > 0)
    {
        prefArrayMade = true;
        numPrefCustomers = lineCount;
        prefCustomers = new Customer*[numPrefCustomers];
        // fill the preferred array using the preferred customer file
        fillPreferredArray(prefCustomerFile, prefCustomers, numPrefCustomers);
    }

    std::cout << "Please enter the orders file name: " << std::endl;
    std::string ordersFile;
    std::cin >> ordersFile;
    std::ifstream ordersFileInput;
    ordersFileInput.open(ordersFile);
    if(!ordersFileInput)
    {
        std::cout << "Invalid file name. Closing Program...: " << std::endl;
        ordersFileInput.close();
        return 3;
    }
    while(getline(ordersFileInput, line))
    {
        bool customerFound = false;
        std::string id, drinkSize, drinkType;
        double sqInchPrice;
        int numDrinks;
        std::string word;
        
        std::istringstream iss(line);
        int numSpacesInLine = 0;
        for(char c : line)
        {
            if(isspace(c))
            {
                numSpacesInLine++;
            }
        }
        // if there are too many fields
        if(numSpacesInLine != 4)
        {
            continue;
        }
        std::getline(iss, id, ' ');
        // if the customer id is not linked to a real customer
        if(findRegularIndex(regCustomers, numRegCustomers, id) == -1 && findPreferredIndex(prefCustomers, numPrefCustomers, id) == -1)
        {
            continue;
        }
        std::getline(iss, drinkSize, ' ');
        std::getline(iss, drinkType, ' ');
        std::getline(iss, word, ' ');
        sqInchPrice = std::stod(word);
        std::getline(iss, word, ' ');
        numDrinks = std::stoi(word);
        // validating the drink size, drink type. making sure that the number of drinks is a positive number, and that the square inch price is not negative
        if((numDrinks > 0) && (drinkSize == "S" || drinkSize == "M" || drinkSize == "L") && (sqInchPrice >= 0) && (drinkType == "soda" || drinkType == "punch" || drinkType == "tea"))
        {
            for(int i = 0; i < numRegCustomers; i++)
            {
                // if the customer is found in the regular array
                if(regCustomers[i]->getID() == id)
                {
                    customerFound = true;
                    // calculate drink price
                    double drinkPrice = calculatePrice(drinkSize, drinkType, sqInchPrice, numDrinks);
                    // set customer's new total amount spent
                    regCustomers[i]->setAmount(regCustomers[i]->getAmount() + drinkPrice);
                    // if regular customer is eligible for upgrade
                    if(regCustomers[i]->getAmount() >= 50)
                    {
                        double amount = regCustomers[i]->getAmount();
                        double discount;
                        // calculating discount if the customer is only upgrading to gold
                        if(amount <= 99.99)
                        {
                            discount = 0.05;
                        }
                        else if(amount <= 149.99)
                        {
                            discount = 0.1;
                        }
                        else if(amount <= 199.99)
                        {
                            discount = 0.15;
                        }
                        // if there are already preferred customers and there is a preferred array
                        if(prefArrayMade == true)
                        {
                            // if customer is able to upgrade to gold, but not platinum
                            if(amount <= 199.99)
                            {
                                // create new Gold Customer with regular customer's credentials
                                Gold *newGold = new Gold(regCustomers[i]->getFirstName(), regCustomers[i]->getLastName(), regCustomers[i]->getID(), amount, discount);
                                // add promoting customer to preferred array
                                prefCustomers = addCustomer(prefCustomers, numPrefCustomers, newGold);
                                // remove upgrading customer from regular array
                                regCustomers = removeFromRegular(regCustomers, numRegCustomers, i);
                                numPrefCustomers++;
                                numRegCustomers--;
                            }
                            // customer is eligible to upgrade straight to platinum
                            else
                            {
                                // make new platinum Customer with regular customer's credentials
                                Platinum *newPlatinum = new Platinum(regCustomers[i]->getFirstName(), regCustomers[i]->getLastName(), regCustomers[i]->getID(), amount, calculateBonusBucks(amount, 0));
                                // add promoting customer to preferred array
                                prefCustomers = addCustomer(prefCustomers, numPrefCustomers, newPlatinum);
                                // remove promoting customer from regular array
                                regCustomers = removeFromRegular(regCustomers, numRegCustomers, i);
                                numPrefCustomers++;
                                numRegCustomers--;
                            }
                        }
                        // if there is no preferred array
                        else
                        {
                            numPrefCustomers++;
                            numRegCustomers--;
                            prefArrayMade = true;
                            // if customer is eligible for gold upgrade but not platinum
                            if(amount <= 199.99)
                            {
                                // create a new gold customer with same attributes as before, but with a discount
                                Gold *newGold = new Gold(regCustomers[i]->getFirstName(), regCustomers[i]->getLastName(), regCustomers[i]->getID(), regCustomers[i]->getAmount(), discount);
                                // create a new preferred array since there wasn't one created yet
                                prefCustomers = new Customer*[numPrefCustomers];
                                // set the first index to the new gold customer, since size is only 1
                                prefCustomers[0] = newGold;
                                // create new regular customers array so that we can remove the customer getting upgraded
                                Customer **newRegArray = new Customer*[numRegCustomers];
                                int j = 0;
                                // every customer that isn't the one getting upgraded gets put into the new array with the same ordering without the upgraded customer
                                for(int p = 0; p < numRegCustomers + 1; p++)
                                {
                                    if(p != i)
                                    {
                                        Customer *newCustomer = new Customer(regCustomers[p]->getFirstName(), regCustomers[p]->getLastName(), regCustomers[p]->getID(), regCustomers[p]->getAmount());
                                        newRegArray[j] = newCustomer;
                                        j++;
                                    }
                                    delete regCustomers[p];
                                }
                                // delete the old customer array
                                delete[] regCustomers;
                                // make a new customer array so that we can copy the data over to the array that we actually use
                                regCustomers = new Customer*[numRegCustomers];
                                // use newRegArray's customers to transfer back to regArray
                                for(int p = 0; p < numRegCustomers; p++)
                                {
                                    // create new customer in order to put back into array
                                    Customer *newCustomer = new Customer(newRegArray[p]->getFirstName(), newRegArray[p]->getLastName(), newRegArray[p]->getID(), newRegArray[p]->getAmount());
                                    regCustomers[p] = newCustomer;
                                    delete newRegArray[p];
                                }
                                delete[] newRegArray;
                            }
                            // if customer is eligible to upgrade straight to platinum
                            else
                            {
                                int bonusBucks = calculateBonusBucks(amount, 0);
                                Platinum *newPlat = new Platinum(regCustomers[i]->getFirstName(), regCustomers[i]->getLastName(), regCustomers[i]->getID(), regCustomers[i]->getAmount(), bonusBucks);
                                prefCustomers = new Customer*[numPrefCustomers];
                                prefCustomers[0] = newPlat;
                                Customer **newRegArray = new Customer*[numRegCustomers];
                                int j = 0;
                                // every customer that isn't the one getting upgraded gets put into the new array with the same ordering without the upgraded customer
                                for(int p = 0; p < numRegCustomers + 1; p++)
                                {
                                    if(p != i)
                                    {
                                        Customer *newCustomer = new Customer(regCustomers[p]->getFirstName(), regCustomers[p]->getLastName(), regCustomers[p]->getID(), regCustomers[p]->getAmount());
                                        newRegArray[p] = newCustomer;
                                        // delete object that pointer at each index of pointer array points to
                                        delete regCustomers[p];
                                        j++;
                                    }
                                }
                                // delete the old customer array
                                delete[] regCustomers;
                                // make a new customer array so that we can copy the data over to the array that we actually use
                                regCustomers = new Customer*[numRegCustomers];
                                // use newRegArray's customers to transfer back to regArray
                                for(int p = 0; p < numRegCustomers; p++)
                                {
                                    // create new customer in order to put back into array
                                    Customer *newCustomer = new Customer(newRegArray[p]->getFirstName(), newRegArray[p]->getLastName(), newRegArray[p]->getID(), newRegArray[p]->getAmount());
                                    regCustomers[p] = newCustomer;
                                    delete newRegArray[p];
                                }
                                delete[] newRegArray;
                            }
                        }
                    }
                }
            }
            //std::cout << prefCustomers[0]->getFirstName() << std::endl;
            if(prefArrayMade && !customerFound)
            {
                for(int i = 0; i < numPrefCustomers; i++)
                {
                    // customer is found in the preferred array
                    if(prefCustomers[i]->getID() == id)
                    {
                        // if the customer is a Gold Customer
                        if(dynamic_cast<Gold*>(prefCustomers[i]))
                        {
                            customerFound = true;
                            Gold *pG = dynamic_cast<Gold*>(prefCustomers[i]);
                            // calculate the price of the drink and applying their discount
                            double drinkPrice = calculatePrice(drinkSize, drinkType, sqInchPrice, numDrinks) - (calculatePrice(drinkSize, drinkType, sqInchPrice, numDrinks) * pG->getDiscount());
                            // update the customer's amount spent
                            pG->setAmount(pG->getAmount() + drinkPrice);
                            // setting the gold customer's new discount, if any
                            if(pG->getAmount() >= 100 && pG->getAmount() <= 149.99)
                            {
                                pG->setDiscount(0.1);
                            }
                            else if(pG->getAmount() >= 149.99 && pG->getAmount() <= 199.99)
                            {
                                pG->setDiscount(0.15);
                            }
                            // the gold customer spent enough to get upgraded to platinum
                            else if(pG->getAmount() >= 200)
                            {
                                // creates a new platinum customer with the gold customer's credentials and is inserted at the same index
                                Platinum *goldToPlat = new Platinum(pG->getFirstName(), pG->getLastName(), pG->getID(), pG->getAmount(), calculateBonusBucks(pG->getAmount(), 0));
                                delete prefCustomers[i];
                                prefCustomers[i] = goldToPlat;
                            }
                        }
                        // the customer is a Platinum Customer
                        else
                        {
                            customerFound = true;
                            Platinum *pP = dynamic_cast<Platinum*>(prefCustomers[i]);
                            // keep their amount spent before the transaction in order to calculate the bonus bucks they earned
                            double oldAmountSpent = pP->getAmount();
                            // calculate the drink price without any bonus bucks being used
                            double drinkPrice = calculatePrice(drinkSize, drinkType, sqInchPrice, numDrinks);
                            int bonusBucksUsed = 0;
                            // if the customer has any bonus bucks to be used
                            if(pP->getBonusBucks() > 0)
                            {
                                // set the amount of bonus bucks used to the smaller number between the price and the customer's current amount of bonus bucks
                                bonusBucksUsed = std::min((int)drinkPrice, pP->getBonusBucks());
                                // decrease the customer's amount of bonus bucks by the amount of bonus bucks used
                                pP->setBonusBucks(pP->getBonusBucks() - bonusBucksUsed);
                                // subtract the number of bonus bucks used from the drink price
                                drinkPrice = drinkPrice - bonusBucksUsed;
                                // if the drink price is less than a dollar but not 0 and the customer still has bonus bucks
                                if(drinkPrice <= 1 && drinkPrice > 0 && pP->getBonusBucks() >= 1)
                                {
                                    // the drink price is now 0 because there were enough bonus bucks to cover the transaction
                                    drinkPrice = 0;
                                    // take away the bonus buck used to cover the rest of the transaction
                                    pP->setBonusBucks(pP->getBonusBucks() - 1);
                                }
                            }
                            // update the customer's amount spent
                            pP->setAmount(pP->getAmount() + drinkPrice);
                            // if there weren't enough bonus bucks to cover the transaction
                            if(drinkPrice > 0)
                            {
                                // use (drink price plus the old amount spent % 5) divided by 5 in order to find out if they went over any multiples of 5
                                double newBonusBucks = drinkPrice + fmod(oldAmountSpent, 5);
                                newBonusBucks = (int)newBonusBucks / 5;
                                // set the customers new bonus bucks amount to the bonus bucks they earned in addition to any bonus bucks that they might have
                                pP->setBonusBucks((int)newBonusBucks);
                            }
                        }
                    }
                }
            }
        }
    }
    // write the customers into file
    std::ofstream regCustomerOutputFile("customer.dat");
    regCustomerOutputFile << regularToFile(regCustomers, numRegCustomers);
    regCustomerOutputFile.close();
    std::ofstream prefCustomerOutputFile("preferred.dat");
    prefCustomerOutputFile << preferredToFile(prefCustomers, numPrefCustomers);
    prefCustomerOutputFile.close();
    // go through array and delete each index
    for(int i = 0; i < numRegCustomers; i++)
    {
        delete regCustomers[i];
    }
    // delete the array
    delete[] regCustomers;
    // go through array and delete each index
    for(int i = 0; i < numPrefCustomers; i++)
    {
        delete prefCustomers[i];
    }
    // delete the array
    delete[] prefCustomers;
}

void fillRegularArray(std::string fileInput, Customer *array[], int numCustomers)
{
    std::ifstream customerFileInput;
    customerFileInput.open(fileInput);
    std::string line;
    for(int i = 0; i < numCustomers; i++)
    {
        std::string word;
        std::string id;
        std::string firstName;
        std::string lastName;
        double amountSpent;
        // get the line from the file
        getline(customerFileInput, line);
        std::istringstream iss(line);
        // get each word in the line
        std::getline(iss, word, ' ');
        // first word is the customer id
        id = word;
        std::getline(iss, word, ' ');
        // next word is the first name
        firstName = word;
        std::getline(iss, word, ' ');
        // next word is the last name
        lastName = word;
        std::getline(iss, word, ' ');
        // last thing is the amount spent
        amountSpent = std::stod(word);
        // make a new customer using each of the values in the line
        Customer *regCustomer = new Customer(firstName, lastName, id, amountSpent);
        // add the customer into the array
        array[i] = regCustomer;
    }
}

void fillPreferredArray(std::string fileInput, Customer *array[], int numCustomers)
{
    std::ifstream customerFileInput;
    customerFileInput.open(fileInput);
    std::string line;
    for(int i = 0; i < numCustomers; i++)
    {
        std::string word;
        std::string firstName;
        std::string lastName;
        std::string id;
        double amountSpent;
        double discount;
        int bonusBucks;
        std::string discountString;
        // get the line from the file
        getline(customerFileInput, line);
        std::istringstream iss(line);
        std::getline(iss, word, ' ');
        // first thing in the line is the customer id
        id = word;
        std::getline(iss, word, ' ');
        // next thing in the line is the customer's first name
        firstName = word;
        std::getline(iss, word, ' ');
        // next thing in the line is the customer's last name
        lastName = word;
        std::getline(iss, word, ' ');
        // next thing in line is amount spent
        amountSpent = std::stod(word);
        // next thing in the line is either the discount or the number of bonus bucks
        std::getline(iss, word, ' ');
        // if there is a percent, then its a gold customer with a discount
        int pos = (int)word.find('%');
        if(pos != (int)std::string::npos)
        {
            std::string sub = word.substr(0, pos);
            discount = std::stod(sub);
            discount = discount / 100;
            Gold *goldCustomer = new Gold(firstName, lastName, id, amountSpent, discount);
            array[i] = goldCustomer;
        }
        // if there is no '%' then it is a platinum customer with bonus bucks
        else
        {
            bonusBucks = std::stoi(word);
            Platinum *platinumCustomer = new Platinum(firstName, lastName, id, amountSpent, bonusBucks);
            array[i] = platinumCustomer;
        }
    }
}

double calculatePrice(std::string size, std::string drinkType, double sqInchPrice, int numDrinks)
{
    double diameter = 0;
    double height = 0;
    int numOunces = 0;
    double drinkPrice = 0;
    // determining the dimensions of the cup
    if(size == "S")
    {
        diameter = 4;
        height = 4.5;
        numOunces = 12;
    }
    if(size == "M")
    {
        diameter = 4.5;
        height = 5.75;
        numOunces = 20;
    }
    if(size == "L")
    {
        diameter = 5.5;
        height = 7;
        numOunces = 32;
    }
    // determining the drink price per ounce
    if(drinkType == "soda")
    {
        drinkPrice = 0.20;
    }
    if(drinkType == "punch")
    {
        drinkPrice = 0.15;
    }
    if(drinkType == "tea")
    {
        drinkPrice = 0.12;
    }
    // calculate the surface area of the cup
    double surfaceArea = 2 * M_PI * (diameter / 2) * height;
    // calculate the price of the drink (not including the personalization)
    double priceOfDrink = drinkPrice * numOunces;
    // calculate the price for personalization
    double personalizePrice = surfaceArea * sqInchPrice;
    // add the price of the drink and the personalization price, then multiply that by the number of drinks the customer wants
    double totalPrice = (priceOfDrink + personalizePrice) * numDrinks;
    return totalPrice;
}

Customer** removeFromRegular(Customer *oldArray[], int oldNumRegular, int indexOfCustomer)
{
    int newNumRegular = oldNumRegular - 1;
    // make a new array for the regular customers
    Customer **newArray = new Customer*[newNumRegular];
    int j = 0;
    for(int i = 0; i < oldNumRegular; i++)
    {
        //as long as the index of the customer getting removed isn't the same as i, add the customer to the new array
        if(i != indexOfCustomer)
        {
            Customer *newCustomer = new Customer(oldArray[i]->getFirstName(), oldArray[i]->getLastName(), oldArray[i]->getID(), oldArray[i]->getAmount());
            newArray[j] = newCustomer;
            j++;
        }
        delete oldArray[i];
    }
    delete[] oldArray;
    return newArray;
}

Customer** addCustomer(Customer *oldArray[], int oldNumPreferred, Customer *upgradingCustomer)
{
    int newNumPreferred = oldNumPreferred + 1;
    // create a new array for the preferred customers
    Customer **newArray = new Customer*[newNumPreferred];
    for(int i = 0; i < oldNumPreferred; i++)
    {
        // if the customer at the index is a Gold Customer
        if(dynamic_cast<Gold*>(oldArray[i]))
        {
            Gold *gPtr = dynamic_cast<Gold*>(oldArray[i]);
            Gold *newGold = new Gold(gPtr->getFirstName(), gPtr->getLastName(), gPtr->getID(), gPtr->getAmount(), gPtr->getDiscount());
            newArray[i] = newGold;
            delete oldArray[i];
        }
        // the customer at the index is a Platinum Customer
        else
        {
            Platinum *pPtr = dynamic_cast<Platinum*>(oldArray[i]);
            Platinum *newPlatinum = new Platinum(pPtr->getFirstName(), pPtr->getLastName(), pPtr->getID(), pPtr->getAmount(), pPtr->getBonusBucks());
            newArray[i] = newPlatinum;
            delete oldArray[i];
        }
    }
    delete[] oldArray;
    // the last index is the customer getting promoted
    newArray[oldNumPreferred] = upgradingCustomer;
    return newArray;
}

std::string regularToFile(Customer *regArray[], int numRegular)
{
    std::string s;
    for(int i = 0; i < numRegular; i++)
    {
        s += regArray[i]->getID();
        s += " ";
        s += regArray[i]->getFirstName();
        s += " ";
        s += regArray[i]->getLastName();
        s += " ";
        std::stringstream stream;
        stream << std::fixed << std::setprecision(2) << regArray[i]->getAmount();
        s += stream.str();
        if(i < numRegular - 1)
        {
            s += "\n";
        }
    }
    return s;
}

std::string preferredToFile(Customer *prefArray[], int numPreferred)
{
    std::string s;
    for(int i = 0; i < numPreferred; i++)
    {
        s += prefArray[i]->getID();
        s += " ";
        s += prefArray[i]->getFirstName();
        s += " ";
        s += prefArray[i]->getLastName();
        s += " ";
        std::stringstream stream;
        stream << std::fixed << std::setprecision(2) << prefArray[i]->getAmount();
        s += stream.str();
        s += " ";
        // if the index holds a Gold Customer
        if(dynamic_cast<Gold*>(prefArray[i]))
        {
            std::stringstream ss;
            Gold *gPtr = dynamic_cast<Gold*>(prefArray[i]);
            // convert the discount from decimal to whole number
            double discountAsWhole = (gPtr->getDiscount()) * 100;
            ss << discountAsWhole;
            s += ss.str();
            s += "%";
        }
        // if the index holds a Platinum Customer
        else
        {
            std::stringstream ss;
            Platinum *platPtr = dynamic_cast<Platinum*>(prefArray[i]);
            ss << platPtr->getBonusBucks();
            s += ss.str();
        }
        // so that there isn't an extra newline character
        if(i < numPreferred - 1)
        {
            s += "\n";
        }
    }
    return s;
}

int calculateBonusBucks(double amountSpent, int numBonusBucks)
{
    return (int)(((amountSpent - 200) / 5) - numBonusBucks);
}

int findRegularIndex(Customer *regArray[], int numRegular, std::string id)
{
    for(int i = 0; i < numRegular; i++)
    {
        if(regArray[i]->getID() == id)
        {
            return i;
        }
    }
    return -1;
}

int findPreferredIndex(Customer *prefArray[], int numPreferred, std::string id)
{
    for(int i = 0; i < numPreferred; i++)
    {
        if(prefArray[i]->getID() == id)
        {
            return i;
        }
    }
    return -1;
}
