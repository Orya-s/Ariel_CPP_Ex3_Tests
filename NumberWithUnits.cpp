#include "NumberWithUnits.hpp"
#include <stdexcept>


using namespace std;

namespace ariel
{

    void NumberWithUnits::read_units(const std::ifstream& units_file)
    {
        string line;
    }

    // binary operators
    const NumberWithUnits NumberWithUnits::operator -(const NumberWithUnits& other) const
    {
        return NumberWithUnits();
    }
    const NumberWithUnits NumberWithUnits::operator +(const NumberWithUnits& other) const
    {
        return NumberWithUnits();
    }
    NumberWithUnits& NumberWithUnits::operator -=(const NumberWithUnits& other)
    {
        //NumberWithUnits n = NumberWithUnits();
        return *this;
    }
    NumberWithUnits& NumberWithUnits::operator +=(const NumberWithUnits& other)
    {
        return *this;
    }

    // friend global binary operators
    bool operator ==(const NumberWithUnits& n1, const NumberWithUnits& n2)
    {
        return false;
    }
    bool operator !=(const NumberWithUnits& n1, const NumberWithUnits& n2)
    {
        return false;
    }
    bool operator >=(const NumberWithUnits& n1, const NumberWithUnits& n2)
    {
        return false;
    }
    bool operator <=(const NumberWithUnits& n1, const NumberWithUnits& n2)
    {
        return false;
    }
    bool operator <(const NumberWithUnits& n1, const NumberWithUnits& n2)
    {
        return false;
    }
    bool operator >(const NumberWithUnits& n1, const NumberWithUnits& n2)
    {
        return false;
    }

    // friend global IO operators
    istream& operator >>(std::istream& is, const NumberWithUnits& n)
    {
        return is;
    }

};