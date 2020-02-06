// array.cpp
// implements array_poly + has main function to take input and so shit

#include <iostream>
#include "array.h"
using namespace std;

// -----------------------------------------------------------------
// CONSTRUCTORS

array_poly::array_poly(): size(-1), arr_poly(nullptr) {}

array_poly::array_poly(vector<int> vect_poly):
	size(vect_poly[vect_poly.size()-1]+1) {  // make size of array_poly 1 more than highest degree of polynomial
		// max degree = last index of vect_poly
	arr_poly = new int[size];  // make array all zeros w/ correct size
	this->readPoly(vect_poly);  // translates input vector to polynomial array
}

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
void array_poly::readPoly(vector<int> vect_poly) {
	for (int i=0; i<vect_poly.size(); i+=2)
		arr_poly[vect_poly[i+1]] += vect_poly[i];  // adds terms together w/ same exponents
}

array_poly array_poly::addPoly(array_poly other) {
	vector<int> v;
	for (int i=0; i<size; i++) {
		if (arr_poly[i]!=0) {
			v.push_back(arr_poly[i]);
			v.push_back(i);
		}
	}
	for (int i=0; i<other.getSize(); i++) {
		if (*(other.getArray()+i)!=0) {
			v.push_back(*(other.getArray()+i));
			v.push_back(i);
		}
	}
	return array_poly(v);
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
