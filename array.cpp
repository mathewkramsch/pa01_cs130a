// array.cpp
// implements array_poly + has main function to take input and do shit

#include <iostream>
#include "array.h"
#include "exceptions.h"
using namespace std;

// -----------------------------------------------------------------
// CONSTRUCTORS

array_poly::array_poly(): size(-1), arr_poly(nullptr) {}

// array_poly::array_poly(vector<int> vect_poly):
	// size(vect_poly[vect_poly.size()-1]+1) {  // make size of array_poly 1 more than highest degree of polynomial
		// // max degree = last index of vect_poly
	// arr_poly = new int[size]{0};  // make array all zeros w/ correct size
	// this->readPoly(vect_poly);  // translates input vector to polynomial array
// }

array_poly::array_poly(string str_poly) {  



	// make size of arrary =  highest degree of polynomial + 1 (so max degree exponenet will be indexable)
	string num="";
	int index_of_largest_exp;  // index of largest exponent = last index of str_poly that is not ' '
	for (int i=str_poly.length()-1; str_poly[i]!=' '; i--)
		index_of_largest_exp=i;
	for (int i=index_of_largest_exp; i<str_poly.length(); i++)
		num += str_poly[i];
	if (num=="") {
		size=0;
		return;
	}
	else size = stoi(num) + 1;

	arr_poly = new int[size]{0};  // make array all zeros w/ correct size
	this->readPoly(str_poly);  // translates input vector to polynomial array
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
// METHODS

string array_poly::writePoly() {
	string output="";
	for (int i=0; i<size; i++) {
		if (arr_poly[i] != 0) {
			output += to_string(arr_poly[i]) + " ";
			output += to_string(i) + " ";
		}
	}
	return output;
}

// translates vect_poly (command-line input in vector form) -> array rep. of polynomial
// adds coefficients to index of array that matches their respective degrees
// void array_poly::readPoly(vector<int> vect_poly) {
	// for (int i=0; i<vect_poly.size(); i+=2) {
		// if (vect_poly[i+1]>size) throw outOfOrderPoly();
		// arr_poly[vect_poly[i+1]] += vect_poly[i];  // adds terms together w/ same exponents
	// }
// }


// helper function for vectorize_input
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

// translates vect_poly (command-line input in vector form) -> array rep. of polynomial
// adds coefficients to index of array that matches their respective degrees
void array_poly::readPoly(std::string str_poly) {
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


array_poly array_poly::addPoly(array_poly other) {
	int size3;
	if (size>other.getSize()) size3 = size;
	else size3 = other.getSize();
	int *arr3 = new int[size3]{0};
	for (int i=0; i<size; i++)
		if (arr_poly[i]!=0) arr3[i] += arr_poly[i];
	for (int i=0; i<other.getSize(); i++)
		if (other.getArray()[i]!=0) arr3[i] += other.getArray()[i];	
	return array_poly(size3,arr3);
}

array_poly array_poly::mulPoly(array_poly other) {
	return other;
}

array_poly array_poly::squPoly() {
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
