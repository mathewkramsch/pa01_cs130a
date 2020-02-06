// exceptions.cpp

#include <iostream>
#include "exceptions.h"
using namespace std;

void noInput::mssg() { cout << "No Input. Ex: ./array.out \"6 8 + 9 0\"" << endl; }
void invalidOperator::mssg() { cout << "Invalid operator. Operators include: *, +, or **" << endl; }
void invalidPolynomial::mssg() { cout << "Invalid polynomial. Ex: 5 0 6 7 = 5x^0 + 6x^7" << endl; }
void invalidOperation::mssg() { cout << "Invalid Operation. Ex: 6 7 * 8 3" << endl; }
void outOfOrderPoly::mssg() { cout << "Polynomial Exponents must be in order of largest to greatest" << endl; }
