#include "Gold.h"

Gold::Gold() : Customer()
{
    discount = 0.0;
}

Gold::Gold(std::string f, std::string l, std::string id, double amount, double d) : Customer(f, l, id, amount)
{
    discount = d;
}
