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

            if (units.find(firstUnit) == units.end())  // if the unit isn't already in the map
            {
                map<string,double> inMap;   // creating the inside convertion map
                units.insert(pair<string, map<string, double>>(firstUnit,inMap));
            }

            if (units.find(secondUnit) == units.end())  // if the unit isn't already in the map
            {
                map<string,double> inMap;   // creating the inside convertion map
                units.insert(pair<string, map<string, double>>(secondUnit,inMap));                
            }
            

            for (const auto& idx : units.at(firstUnit))  // adding convertion to all the matching units
            {
                double conv = idx.second * val;
                units.at(idx.first).insert(pair<string,double>(secondUnit, conv));
                units.at(secondUnit).insert(pair<string,double>(idx.first, 1 / conv));
            }    

            for (const auto& idx : units.at(secondUnit))  // adding convertion to all the matching units
            {
                double conv = idx.second * val;
                units.at(idx.first).insert(pair<string,double>(firstUnit, 1 / conv));
                units.at(firstUnit).insert(pair<string,double>(idx.first, conv));
            }

            units.at(firstUnit).insert(pair<string,double>(secondUnit, val));
            units.at(secondUnit).insert(pair<string,double>(firstUnit, 1 / val));

        }  // end of while

        units_file.close(); 
    }  // end of read_units


    bool canConvert(const string& firstUnit, const string& secondUnit)
    {
        return NumberWithUnits::units.at(firstUnit).count(secondUnit);
    }


    // binary operators 
    const NumberWithUnits NumberWithUnits::operator -(const NumberWithUnits& other)
    {
        if (unit == other.unit)
        {
            return NumberWithUnits(num-other.num, unit);
        }
        else
        {
            if (!canConvert(unit,other.unit))
            {
                throw invalid_argument(unit + " cannot be converted to " + other.unit);
            }
            else
            {
            
            }            
        }

        return *this;
    }
    const NumberWithUnits NumberWithUnits::operator +(const NumberWithUnits& other)
    {
        return -(*this - other);
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
        return !(n1 == n2);
    }
    bool operator >=(const NumberWithUnits& n1, const NumberWithUnits& n2)
    {
        return !(n1 < n2);
    }
    bool operator <=(const NumberWithUnits& n1, const NumberWithUnits& n2)
    {
        return !(n1 > n2);
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