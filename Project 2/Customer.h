#ifndef Customer_h
#define Customer_h
#include <iostream>

class Customer
{
    private:
        std::string firstName;
        std::string lastName;
        std::string guestID;
        double amountSpent;
    public:
        Customer() { firstName = ""; lastName = ""; guestID = ""; amountSpent = 0; }
        Customer(std::string f, std::string l, std::string id, double amount) { firstName = f; lastName = l; guestID = id; amountSpent = amount;}
        virtual ~Customer(){}
        virtual std::string getFirstName() const { return firstName; }
        std::string getLastName() { return lastName; }
        std::string getID() { return guestID; }
        double getAmount() { return amountSpent; }
        void setFirstName(std::string f) { firstName = f; }
        void setLastName(std::string l) { lastName = l; }
        void setID(std::string id) { guestID = id; }
        void setAmount(double amount) { amountSpent = amount; }
};

#endif
