// array.h

#ifndef ARRAY_H
#define ARRAY_H
#include "string"

class array_poly {
	public:
		// CONSTRUCTORS
		array_poly();
		array_poly(std::string str_poly);
		array_poly(int size1, int *arr);
		array_poly& operator =(const array_poly &right);

		// GETTERS
		int getSize() const { return size; }
		int* getArray() const {return arr_poly; }

		// PUBLIC METHODS
		std::string writePoly();  // array polynomial -> string representation
		array_poly addPoly(array_poly other);  // adds this poly w/ other -> = 3rd poly
		array_poly mulPoly(array_poly other);  // multiplies this poly w/ other -> = 3rd poly
		array_poly squPoly();  // squares this poly -> = 3rd poly

		// temporary method for debugging:
		void print(int num);
	private:
		// PRIVATE VARIABLES
		int size;  // size of arr_poly
		int* arr_poly;  // array to represent input polynomial, arr_poly[exponent] = coefficient

		// HELPER FUNCTIONS
		void readPoly(std::string str_poly);  // translates str_poly string to arr_poly
		std::pair<int,int> readNumber(std::string input, int i);  // helper function for readPoly
};

#endif
