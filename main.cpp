// main.cpp

#include <iostream>
#include "mainFuncs.h"
#include "exceptions.h"
#include "array.h"
using namespace std;

int main(int argc, char *argv[]) {  // argc = # inputs, argv[] = cstring of inputs

	char operation = '?';
	pair<vector<int>,vector<int>> vect_polys;
	try {

		if (argc!=2) throw noInput();

		operation = get_operation(argv[1]);  // find out which operation to perform
		vect_polys = vectorize_input(argv[1]);  // get pair of each polynomial as vector
		array_poly a1(vect_polys.first);  // make array_poly object for 1st polynomial
		array_poly a3;



		// array_poly a2(vect_polys.second);
// 
		// print_vector(vect_polys.first,1);
		// a1.print(1);
// 
		// print_vector(vect_polys.second,2);
		// a2.print(2);
// 
 
		if (operation=='+') {
			array_poly a2(vect_polys.second);  // make 2nd polynomial's array_poly object
			a3 = a1.addPoly(a2);
		} else if (operation=='*') {
			array_poly a2(vect_polys.second);  // make 2nd polynomial's array_poly object
			a3 = a1.mulPoly(a2);
		} else if (operation=='^') a3 = a1.squPoly();

		cout << a3.writePoly() << endl;
		a3.print(3);

	} catch (noInput e) { e.mssg();
	} catch (invalidOperator e) { e.mssg(); 
	} catch (invalidPolynomial e) { e.mssg();
	} catch (invalidOperation e) { e.mssg();
	} catch (outOfOrderPoly e) { e.mssg();
	}

	return 0;
}
