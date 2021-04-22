/**
 * Author: Orya Spiegel
 */

#include "doctest.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "NumberWithUnits.hpp"
using namespace ariel;


///NumberWithUnits number;

TEST_CASE("reading from file")
{
    // using a constructor before loading a units file
    CHECK_THROWS(NumberWithUnits b(0.5, "m"));
    CHECK_THROWS(NumberWithUnits c(3, "g"));
    CHECK_THROWS(NumberWithUnits f(6, "min"));
    CHECK_THROWS(NumberWithUnits g(7, "ILS"));
    
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);

    CHECK_NOTHROW(NumberWithUnits a(1, "km"));
    CHECK_NOTHROW(NumberWithUnits b(2, "m"));
    CHECK_NOTHROW(NumberWithUnits c(3, "kg"));
    CHECK_NOTHROW(NumberWithUnits d(4, "ton"));
    CHECK_NOTHROW(NumberWithUnits e(5, "hour"));
    CHECK_NOTHROW(NumberWithUnits f(6, "min"));
    CHECK_NOTHROW(NumberWithUnits g(7, "USD"));

    // non existing units
    CHECK_THROWS(NumberWithUnits i(2, "ml"));
    CHECK_THROWS(NumberWithUnits j(3, "gr"));
    CHECK_THROWS(NumberWithUnits k(4, "lb"));
    CHECK_THROWS(NumberWithUnits l(5, "oz"));
    CHECK_THROWS(NumberWithUnits n(7, "EUR"));
}


TEST_CASE("using binary operators on variables from different dimensions")
{
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    NumberWithUnits a(1, "km");
    NumberWithUnits b(2, "m");
    NumberWithUnits c(3, "kg");
    NumberWithUnits d(4, "ton");
    NumberWithUnits e(5, "hour");

    // +
    CHECK_THROWS(a+c);
    CHECK_THROWS(a+d);
    CHECK_THROWS(a+e);
    CHECK_THROWS(c+a);
    CHECK_THROWS(d+a);
    CHECK_THROWS(e+a);

    // -
    CHECK_THROWS(b-c);
    CHECK_THROWS(b-d);
    CHECK_THROWS(b-e);
    CHECK_THROWS(c-b);
    CHECK_THROWS(d-b);
    CHECK_THROWS(e-b);

    // -=
    CHECK_THROWS(b-=c);
    CHECK_THROWS(b-=d);
    CHECK_THROWS(b-=e);
    CHECK_THROWS(c-=b);
    CHECK_THROWS(d-=b);
    CHECK_THROWS(e-=b);

    // +=
    CHECK_THROWS(a+=c);
    CHECK_THROWS(a+=d);
    CHECK_THROWS(a+=e);
    CHECK_THROWS(c+=a);
    CHECK_THROWS(d+=a);
    CHECK_THROWS(e+=a);

    // ==
    // CHECK_THROWS(bool flag = (c==a));
    // CHECK_THROWS(bool flag = (c==b));
    // CHECK_THROWS(bool flag = (c==e));
    // CHECK_THROWS(bool flag = (a==c));
    // CHECK_THROWS(bool flag = (b==c));
    // CHECK_THROWS(bool flag = (e==c));

    // // !=
    // CHECK(c!=a);
    // CHECK(c!=b);
    // CHECK(c!=e);
    // CHECK(a!=c);
    // CHECK(b!=c);
    // CHECK(e!=c);

    // >=
    // CHECK_THROWS(c>=a);
    // CHECK_THROWS(c>=b);
    // CHECK_THROWS(c>=e);
    // CHECK_THROWS(a>=c);
    // CHECK_THROWS(b>=c);
    // CHECK_THROWS(e>=c);

    // <=

    // >

    // <
}

TEST_CASE("using binary operators on variables from the same dimension")
{
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    NumberWithUnits a1(1, "km");
    NumberWithUnits a2(1, "km");
    NumberWithUnits b(2, "m");
    NumberWithUnits c1(3, "kg");
    NumberWithUnits c2(1.5, "kg");
    NumberWithUnits d(4, "ton");
    NumberWithUnits e1(5, "hour");
    NumberWithUnits e2(10, "hour");
    NumberWithUnits f(6, "min");
    NumberWithUnits g1(7, "USD");
    NumberWithUnits g2(0.5, "USD");

    // -
    CHECK(a1-a2 == NumberWithUnits(0,"km"));
    CHECK(a1-b == NumberWithUnits(0.998,"km"));
    CHECK(c1-c2 == NumberWithUnits(1.5,"kg"));
    CHECK(e1-e2 == NumberWithUnits(-5,"hour"));
    CHECK(e1-f == NumberWithUnits(4.9,"hour"));
    CHECK(g1-g2 == NumberWithUnits(6.5,"USD"));

    // +
    CHECK(a1+a2 == NumberWithUnits(2,"km"));
    CHECK(a1+b == NumberWithUnits(1.002,"km"));
    CHECK(c1+c2 == NumberWithUnits(4.5,"kg"));
    CHECK(e1+e2 == NumberWithUnits(15,"hour"));
    CHECK(f+e1 == NumberWithUnits(306,"min"));
    CHECK(g1+g2 == NumberWithUnits(7.5,"USD"));

    // -=

    // +=

    // ==
    CHECK(a1 == a2);
    CHECK((b*500) == a1);
    CHECK(c1 == (c2+c2));
    CHECK(e2 == NumberWithUnits(600,"min"));
    CHECK(f == NumberWithUnits(0.1,"hour"));

    // !=
    CHECK(a1 != NumberWithUnits(3,"km"));
    CHECK(b != NumberWithUnits(0.2,"km"));
    CHECK(c1 != (c2));
    CHECK(e2 != NumberWithUnits(6,"min"));
    CHECK(f != NumberWithUnits(0.001,"hour"));
    
    // >=

    // <=

    // >

    // <
}

TEST_CASE("using unary operators")
{
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    NumberWithUnits a(1, "km");
    NumberWithUnits b(2, "m");
    NumberWithUnits c(3, "kg");
    NumberWithUnits d(4, "ton");
    NumberWithUnits e(5, "hour");
    NumberWithUnits f(7, "USD");

    // -
    CHECK(-a == NumberWithUnits(-1,"km"));
    CHECK(-c == NumberWithUnits(-3,"kg"));
    CHECK(-d == NumberWithUnits(-4,"ton"));
    CHECK(-f == NumberWithUnits(-7,"USD"));

    // +
    CHECK(+a == NumberWithUnits(1,"km"));
    CHECK(+c == NumberWithUnits(3,"kg"));
    CHECK(+d == NumberWithUnits(4,"ton"));
    CHECK(+f == NumberWithUnits(7,"USD"));

    // ++
    CHECK(++a == NumberWithUnits(2,"km"));
    CHECK(b++ == NumberWithUnits(2,"m"));
    CHECK(b == NumberWithUnits(3,"m"));
    CHECK(++c == NumberWithUnits(4,"kg"));
    CHECK(d++ == NumberWithUnits(4,"ton"));
    CHECK(++e == NumberWithUnits(6,"hour"));

    // --
    CHECK(--a == NumberWithUnits(0,"km"));
    CHECK(b-- == NumberWithUnits(2,"m"));
    CHECK(b == NumberWithUnits(1,"m"));
    CHECK(--c == NumberWithUnits(2,"kg"));
    CHECK(d-- == NumberWithUnits(4,"ton"));
    CHECK(--e == NumberWithUnits(4,"hour"));

    // * double
    CHECK((b*500) == a);
    CHECK((500*b) == a);
    CHECK((c*0.5) == NumberWithUnits(1.5,"km"));
    CHECK((d*0) == NumberWithUnits(0,"ton"));
    CHECK((2*f) == NumberWithUnits(14,"USD"));

    // // << 
    // CHECK((cout << (a+a)) == ("2[km]"));
    // CHECK((cout << (a+b) ) == ("1.002[km]"));
    // CHECK((cout << (f)) == ("7[USD]"));
    // CHECK((cout << (d*0)) == ("0[ton]"));

    // >> 
    istringstream sample_input1{"700 [ kg ]"};
    sample_input1 >> a;
    istringstream sample_input2{"0 [ km]"};
    sample_input2 >> a;
    istringstream sample_input3{"1.2[ton]"};
    sample_input3 >> c;
    istringstream sample_input4{"1000[EUR]"};
    sample_input4 >> f;
}