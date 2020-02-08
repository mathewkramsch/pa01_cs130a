// main.cpp

#include <iostream>
#include "../mainFuncs.h"
#include "../exceptions.h"
#include "ll.h"
using namespace std;

int main(int argc, char *argv[]) {  // argc = # inputs, argv[] = cstring of inputs

	char operation = '?';
	pair<string,string> str_polys;

	try {

		if (argc!=2) throw noInput();

		// GET INPUT
		operation = get_operation(argv[1]);  // find out which operation to perform
		str_polys = parse_input(argv[1]);  // split input into pair of strings for each polynomial
		linkedlist_poly lp1(str_polys.first);  // make linkedlist_poly object for 1st polynomial
		cout << "lp1: " << lp1.writePoly() << endl;

		// ADD/MULTIPLY/SQUARE OPERATIONS:
		linkedlist_poly lp3;
		if (operation=='+') {
			linkedlist_poly lp2(str_polys.second);  // make 2nd polynomial's linkedlist_poly object
			cout << "lp2: " << lp2.writePoly() << endl;
			lp3 = lp1.addPoly(lp2);  // calls destructor for lp2?
		} else if (operation=='*') {
			linkedlist_poly lp2(str_polys.second);  // make 2nd polynomial's linkedlist_poly object
			lp3 = lp1.mulPoly(lp2);
		} else if (operation=='^') lp3 = lp1.squPoly();

		// OUTPUT:
		cout << lp3.writePoly() << endl;

	} catch (noInput e) { e.mssg();
	} catch (invalidOperator e) { e.mssg();
	} catch (invalidPolynomial e) { e.mssg();
	} catch (invalidOperation e) { e.mssg();
	} catch (outOfOrderPoly e) { e.mssg();
	}

	return 0;
}
