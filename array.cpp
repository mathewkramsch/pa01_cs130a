// array.cpp
// implements array_poly + has main function to take input and do shit

#include <iostream>
#include "array.h"
#include "exceptions.h"
using namespace std;

// -----------------------------------------------------------------
// CONSTRUCTORS

array_poly::array_poly(): size(-1), arr_poly(nullptr) {}
// POSTCONDITION: size = -1, arr_poly is a nullptr (so can make array_poly object w/o arguments)

array_poly::array_poly(string str_poly) {  
// PRECONDITION: str_poly is from parse_input, contains one polynomial in string form w/o operators
// POSTCONDITION: size = largest exponent + 1 (so max degree exponent will be indexable)
	// calls readPoly to create arr_poly correctly

	string num="";
	int index_of_largest_exp;  

	// index of largest exponent = last index of str_poly that is not ' '
	for (int i=str_poly.length()-1; str_poly[i]!=' '; i--)
		index_of_largest_exp=i;
	for (int i=index_of_largest_exp; i<str_poly.length(); i++)
		num += str_poly[i];

	// if str_poly == "" (ie. with square operation, no 2nd polynomial)
	if (num=="") {  
		size=0;
		arr_poly=nullptr;
	} else {
		size = stoi(num) + 1;
		arr_poly = new int[size]{0};
		this->readPoly(str_poly);
	}
}

array_poly::array_poly(int size1, int *arr): size(size1), arr_poly(arr) {}

array_poly& array_poly::operator =(const array_poly &right) {
	if (this==&right) return *this;
	if (size>0) delete [] arr_poly;
	size = right.getSize();
	arr_poly = new int[size];
	for (int i=0; i<size; i++)
		*(arr_poly + i) = *(right.getArray() + i);
	return *this;
}
	
// -----------------------------------------------------------------
// READ/WRITE METHODS

string array_poly::writePoly() {
// POSTCONDITION: translates arr_poly to a string format in reduced form: ie. 5 7 8 9 = 5x^7 + 8x^9

	string output="";
	for (int i=0; i<size; i++) {
		if (arr_poly[i] != 0) {
			output += to_string(arr_poly[i]) + " ";
			output += to_string(i) + " ";
		}
	}
	return output;
}

pair<int,int> array_poly::readNumber(string input, int i) {
// PRECONDITION: input is str_poly and i is index of input to start on
// POSTCONDITION: returns pair w/ info
	// first: the number to input into array
	// second: the index of next character to read in str_poly (after number)

	string num="";
	pair<int,int> p;
	int j=i;
	while (input[j]!=' ' && j<input.length())
		num += input[j++];
	p.first = stoi(num);
	p.second = j;
	return p;
}

void array_poly::readPoly(std::string str_poly) {
// PRECONDITION: str_poly is from parse_input, contains one polynomial in string form w/o operators
// POSTCONDITION: translates str_poly -> array rep. of polynomial, writes to arr_poly
	// aka: adds coefficients to index of array that matches their respective degrees

	int i=0;
	bool read_coefficient_next=true;
	int coefficient(0), exponent(0);
	while (i<str_poly.length()) {
		if (str_poly[i]!=' ') {
			pair<int,int> p=readNumber(str_poly,i);
			i=p.second;  // p.second = index of next char to read in str_poly
			if (read_coefficient_next) {
				coefficient = p.first;
				read_coefficient_next=false;
			}
			else {
				exponent = p.first;
				if (i<str_poly.length()-1 && exponent>size) throw outOfOrderPoly();
				arr_poly[exponent] = coefficient;
				read_coefficient_next=true;
			}
		} else i++;
	}
	if (!read_coefficient_next) throw invalidPolynomial();  
		// this means coefficient was last term (each coefficient inputted must have a exponent)
}

// -----------------------------------------------------------------
// OPERATION METHODS

array_poly array_poly::addPoly(array_poly other) {
// PRECONDITION: other is an array_poly object in reduced form
// POSTCONDITION: returns an array_poly object that is = this array_poly + other

	int size3;
	if (size>other.getSize()) size3 = size;  // make size3 = the larger size
	else size3 = other.getSize();
	int *arr3 = new int[size3]{0};  // make the array
	
	for (int i=0; i<size; i++) {  // add from *this arr_poly
		if (arr_poly[i]!=0) {
			arr3[i] += arr_poly[i];
			arr3[i] = arr3[i]%1000000;
		}
	}	
	for (int i=0; i<other.getSize(); i++) {  // add from other arr_poly
		if (other.getArray()[i]!=0) {
			arr3[i] += other.getArray()[i];
			arr3[i] = arr3[i]%1000000;
		}
	}

	return array_poly(size3,arr3);
}

array_poly array_poly::mulPoly(array_poly other) {
// PRECONDITION: other is an array_poly object in reduced form
// POSTCONDITION: returns an array_poly object that is = this array_poly * other

	int size3 = size + other.getSize();  // size3 will be sum of largest degrees of each polynomial
	size3 = size3%10000;  // all exponents = mod 10^4
	int *arr3 = new int[size3]{0};

	int coef1(0), exp1(0);  // coefficient/exponent from this arr_poly
	int coef2(0), exp2(0);  // coefficient/exponent from other's arr_poly
	int coef3(0), exp3(0);  // coefficient/exponent for new array

	for (int i=0; i<size; i++) {
		if (arr_poly[i]!=0) {
			coef1 = arr_poly[i];
			exp1 = i;
			for (int j=0; j<other.getSize(); j++) {
				if (other.getArray()[j]!=0) {
					coef2 = other.getArray()[j];
					exp2 = j;
					exp3 = (exp1+exp2)%10000;  // exponents = mod 10^4
					coef3 = (coef1*coef2)%1000000;  // coefficients = mod 10^6
					arr3[exp3] = coef3;
				}
			}
		}
	}

	return array_poly(size3,arr3);
}

array_poly array_poly::squPoly() {
// PRECONDITION: other is an array_poly object in reduced form
// POSTCONDITION: returns an array_poly object that is = this array_poly^2

	return *this;
}

// -----------------------------------------------------------------
// FOR DEBUGGING

void array_poly::print(int num) {
	cout << "arr_poly" << num << ": ";
	for (int i=0; i<size; i++)
		cout << arr_poly[i] << " ";
	cout << endl;
	cout << "size: " << size << endl;
}
