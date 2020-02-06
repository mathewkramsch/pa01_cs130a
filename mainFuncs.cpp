// mainFuncs.cpp

#include "mainFuncs.h"
#include "exceptions.h"
#include <iostream>
using namespace std;

// -----------------------------------------------------------------
// MAIN HELPER FUNCTIONS

char get_operation(string input) {
	// PRECONDITION: should only take argv[1] as a string
	// POSTCONDITION: returns character of operation to be performed on polynomials
		// returns '+' if add, '*' if multiply, and '^' if square
		// if no operation present, or invalid operation(s), returns '?' character
	
	char operation = '?';
	int count = 0;
	for (int i=0; i<input.length(); i++) {
		if (input[i] == '+') operation = '+';
		else if (input[i] == '*') operation = '*';
		else continue;
		count++;
	}
	if (operation=='+' && count==1) return '+';
	if (operation=='*' && count==1) return '*';
	if (operation=='*' && count==2) return '^';
	throw invalidOperator();
}	

pair<int,int> read_number(string input, int i) {
	string num="";
	pair<int,int> p;
	int j=i;
	while (input[j]!=' ' && j<input.length())
		num += input[j++];
	p.first = stoi(num);
	p.second = j;
	return p;
}


pair<vector<int>,vector<int>> vectorize_input(string input) {
	// PRECONDITION: should only take argv[1] as a string, assumes valid operation in input
	// POSTCONDITION: returns pair of integer vectors, one for each polynomial
		// NOTE: if only one polynomial (such as with square), 2nd vector = empty

	vector<int> v1 = {};
	vector<int> v2 = {};
	bool operator_yet(false), square_operation(false);
	bool add_to_v1(false), add_to_v2(false);
	for (int i=0; i<input.length(); i++) {
		if (input[i] != ' ') {
			if (operator_yet==false) {
				if (input[i]=='+' || input[i]=='*') operator_yet = true;  // dont add operator to vector
				else add_to_v1=true;
			} else if (operator_yet==true) {
				if (input[i]!='*') add_to_v2=true;
				if (input[i]=='*') square_operation = true;
			}
		} if (add_to_v1 || add_to_v2) {
			pair<int,int> p = read_number(input,i);
			i=p.second;
			if (add_to_v1) v1.push_back(p.first);
			else v2.push_back(p.first);
			add_to_v1=false;
			add_to_v2=false;
		}
	}
	if (v1.size()%2==1 || (!v2.empty() && v2.size()%2==1) ) throw invalidPolynomial();
	if (square_operation && !v2.empty()) throw invalidOperation();
	if (v2.empty() && !square_operation) throw invalidOperation();
	pair<vector<int>,vector<int>> vector_pair(v1,v2);
	return vector_pair;
}


// -----------------------------------------------------------------
// FUNCTIONS FOR DEBUGGING

void print_vector(vector<int> v, int num) {
	cout << "vec_poly" << num << ": ";
	for (int i=0; i<v.size(); i++)
		cout << v[i] << " ";
	cout << endl;
}
