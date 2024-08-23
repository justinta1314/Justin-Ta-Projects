#include "DVD.h"

std::ostream& operator<<(std::ostream &out, const DVD &obj)
{
    out << std::left << std::setw(28) << obj.title.substr(1, obj.title.length() - 2);
    out << std::setw(10) << obj.available;
    out << std::left << std::setw(10) << obj.rented;
    out << "\n";
    return out;
}

bool DVD::operator<(const DVD &obj)
{
    bool isLess = false;
    if(this->getTitle() < obj.getTitle())
    {
        isLess = true;
    }
    return isLess;
}

bool DVD::operator>(const DVD &obj)
{
    bool isGreater = false;
    if(this->getTitle() > obj.getTitle())
    {
        isGreater = true;
    }
    return isGreater;
}

bool DVD::operator==(const DVD &obj)
{
    bool isEqual = false;
    if(this->getTitle() == obj.getTitle())
    {
        isEqual = true;
    }
    return isEqual;
}
