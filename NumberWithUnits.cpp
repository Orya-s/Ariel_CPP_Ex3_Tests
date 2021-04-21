#include "NumberWithUnits.hpp"
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <istream>
#include <string>
#include <iostream>


using namespace std;

namespace ariel
{
    map<string, map<string, double>> NumberWithUnits::units;

    void NumberWithUnits::read_units(ifstream& units_file)
    {
        string line;
        int one;
        string firstUnit;
        string split = "=" ;
        double val;
        string secondUnit;
            
        while (getline(units_file, line))
        {
            istringstream iss(line);
            iss >> one >> firstUnit >> split >> val >> secondUnit;

            if (units.find(firstUnit) != units.end())  // if the unit is already in the map
            {
                units.find(firstUnit)->second.insert(pair<string,double>(secondUnit,val)) ;
            }
            else  // adding the unit to the map
            {
                map<string,double> inMap;   // creating the inside convertion map
                inMap.insert(pair<string,double> (secondUnit,val));
                units.insert(pair<string, map<string, double>>(firstUnit,inMap));
            }
            


            // cout << line << endl;
            // cout << firstUnit << "  " << val << secondUnit << endl;
        }
        
        
        
        
        units_file.close(); 
    }



    // binary operators
    const NumberWithUnits NumberWithUnits::operator -(const NumberWithUnits& other) const
    {
        if (unit == other.unit)
        {
            return NumberWithUnits(num-other.num, unit);
        }
        else
        {
            
        }

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