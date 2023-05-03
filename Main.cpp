#include <iostream>
#include "sources/Fraction.hpp"
#include <iostream>
#include <algorithm>
#include <cmath>
#include "doctest.h"
using namespace std;
using namespace ariel;

int main() {
    std::cout << "Hello, world!" << std::endl;
    Fraction d(4, 5);
    float e = 0.4;
    Fraction f = d - e; // 4/5 - 2/5 = 2/5
    cout << f.getNumerator() << endl;
    cout << f.getDenominator() << endl;
    CHECK(((f.getNumerator() == 2) && (f.getDenominator() == 5)));
    CHECK(__gcd(f.getNumerator(), f.getDenominator()) == 1);
    return 0;
}