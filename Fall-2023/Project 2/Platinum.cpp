#include "Platinum.h"

Platinum::Platinum() : Customer()
{
    bonusBucks = 0;
}

Platinum::Platinum(std::string f, std::string l, std::string id, double amount, int b) : Customer(f, l, id, amount)
{
    bonusBucks = b;
}
