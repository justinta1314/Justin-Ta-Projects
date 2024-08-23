#ifndef DVD_h
#define DVD_h

#include <iostream>
#include <string>
#include <iomanip>


class DVD
{
    private:
        std::string title;
        int available;
        int rented;
    public:
        DVD() { title = ""; available = 0; rented = 0; }
        DVD(std::string t, int a, int r) { title = t; available = a; rented = r; }
        void setTitle(std::string t) { title = t; }
        void setAvailable(int a) { available = a; }
        void setRented(int r) { rented = r; }
        std::string getTitle() const { return title; }
        int getAvailable() const { return available; }
        int getRented() const { return rented; }
        friend std::ostream& operator<<(std::ostream&, const DVD&);
        bool operator<(const DVD&);
        bool operator>(const DVD&);
        bool operator==(const DVD&);
};
#endif
