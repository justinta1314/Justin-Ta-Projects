#ifndef Gold_h
#define Gold_h
#include "Customer.h"

class Gold : public Customer
{
    private:
        double discount;
    public:
        Gold();
        Gold(std::string, std::string, std::string, double, double);
        double getDiscount() { return discount; }
        void setDiscount(double newDiscount) { discount = newDiscount; }
};

#endif
