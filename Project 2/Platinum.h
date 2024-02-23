#ifndef Platinum_h
#define Platinum_h
#include "Customer.h"

class Platinum : public Customer
{
    private:
        int bonusBucks;
    public:
        Platinum();
        Platinum(std::string, std::string, std::string, double, int);
        int getBonusBucks() { return bonusBucks; }
        void setBonusBucks(int b) { bonusBucks = b; }
};

#endif
