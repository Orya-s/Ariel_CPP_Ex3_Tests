#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "NumberWithUnits.hpp"
using namespace ariel;

int main() {

    // constructing before reading file
    try 
    {
        NumberWithUnits a{10, "km"}; 
    } 
    catch (const std::exception& ex) 
    {
        cout << ex.what() << endl; 
    }

    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);

    // constructing non existing unit
    try 
    {
        NumberWithUnits a{0.5, "oz"}; 
    } 
    catch (const std::exception& ex) 
    {
        cout << ex.what() << endl; 
    }


    NumberWithUnits a(1, "km");
    NumberWithUnits b(2, "m");
    NumberWithUnits c(3, "kg");

    // using binary operators on variables from different dimensions
    // +
    try 
    {
        cout << a+c << endl; 
    } 
    catch (const std::exception& ex) 
    {
        cout << ex.what() << endl; 
    }
    try 
    {
        cout << c+a << endl; 
    } 
    catch (const std::exception& ex) 
    {
        cout << ex.what() << endl; 
    }
    // -=
    try 
    {
        cout << (b-=c) << endl; 
    } 
    catch (const std::exception& ex) 
    {
        cout << ex.what() << endl; 
    }

    // using binary operators on variables from the same dimensions
    NumberWithUnits d(12, "cm");
    NumberWithUnits e(20, "mm");
    // -
    cout << (a-b) << " -->  should print (1km-2m) = 0.998[km]" << endl;
    cout << (b-e) << " -->  should print (2m-20mm) = 1.98[m]" << endl;
    // +=
    cout << (a+=e) << " -->  should print (1km+20mm) = 1.00002[km]" << endl;
    cout << a << " = a  , now a holds a new value"<< endl;


    // increment & decrement
    cout << b++ << " -->  b is not yet modified" << endl;
    cout << ++b << " -->  b is now 4m" << endl;

    cout << --d << " -->  d is now 11cm" << endl;
    cout << d-- << " -->  d is not yet modified" << endl;
    cout << d << " -->  d is now 10cm" << endl;


    // * double

    cout << a*3 << " -->  a is now (1.00002 * 3) = 3.00006 km" << endl;
    cout << b*0.5 << " -->  b is now 2m" << endl;
    cout << d*0.1 << " -->  d is now 1cm" << endl;


    // friend global binary operators
    NumberWithUnits f(1, "ILS");
    NumberWithUnits g(3, "USD");
    NumberWithUnits h(2, "EUR");

    cout << boolalpha; 
    cout << (a>b) << " -->  true" << endl;  
    cout << (a<=b) << " -->  false" << endl;  
    cout << ((h*0.5) == (f*4)) << " -->  true"  << endl; 
    cout << ((g*5) == (f*0.3)) << " -->  false"  << endl; 


    istringstream input1{"5 [ EUR ]"};
    input1 >> a;
    cout << a << " -->  a is now 5 EUR" << endl; 
    istringstream input2{"3[ ILS ]  "};
    input2 >> a;
    cout << a << " -->  a is now 3 ILS" << endl; 


    return 0;
}
