// main.cpp

#include <iostream>
#include "mainFuncs.h"
#include "exceptions.h"
#include "array.h"
using namespace std;

int main(int argc, char *argv[]) {  // argc = # inputs, argv[] = cstring of inputs

	char operation = '?';
	pair<string,string> str_polys;

	try {

		if (argc!=2) throw noInput();

		// GET INPUT
		operation = get_operation(argv[1]);  // find out which operation to perform
		str_polys = parse_input(argv[1]);  // split input into pair of strings for each polynomial
		array_poly a1(str_polys.first);  // make array_poly object for 1st polynomial

		// ADD/MULTIPLY/SQUARE OPERATIONS:
		array_poly a3;
		if (operation=='+') {
			array_poly a2(str_polys.second);  // make 2nd polynomial's array_poly object
			a3 = a1.addPoly(a2);
		} else if (operation=='*') {
			array_poly a2(str_polys.second);  // make 2nd polynomial's array_poly object
			a3 = a1.mulPoly(a2);
		} else if (operation=='^') a3 = a1.squPoly();

		// OUTPUT:
		cout << a3.writePoly() << endl;

		// DEBUGGING:
		// a3.print(3);

	} catch (noInput e) { e.mssg();
	} catch (invalidOperator e) { e.mssg(); 
	} catch (invalidPolynomial e) { e.mssg();
	} catch (invalidOperation e) { e.mssg();
	} catch (outOfOrderPoly e) { e.mssg();
	}

	return 0;
}
