// ll.cpp

#include "ll.h"
#include "../exceptions.h"
#include <iostream>
using namespace std;

// -----------------------------------------------------------------
// CONSTRUCTORS/DESTRUCTOR

linkedlist_poly::linkedlist_poly(string str_poly): size(0), head(0), tail(0) {
	this->readPoly(str_poly);
}


// linkedlist_poly::linkedlist_poly(int size1, node *head) {}

linkedlist_poly& linkedlist_poly::operator =(const linkedlist_poly &right) {
	if (this == &right) return *this;
	if (head) delete this;
	node *p = right.head;
	while (p) {
		this->insert_end(p->coefficient, p->exponent);
		p = p->next;
	}
	return *this;
}

linkedlist_poly::~linkedlist_poly() {
	node *n = head;
	while (n) {
		node *tmp = n;
		n = n->next;
		delete tmp;
	}
}

// -----------------------------------------------------------------
// PUBLIC METHODS

string linkedlist_poly::writePoly() {
	string output="";
	node *n = head;
	while (n) {
		output += to_string(n->coefficient) + " ";
		output += to_string(n->exponent) + " ";
		n=n->next;
	}
	return output;
}

void linkedlist_poly::addPoly_helper(node *this_node, node *other_node) {
// PRECONDITION: this_node is the head linkedlist wher other_node must be inserted
// POSTCONDITION: other_node is inserted in the correct place in this_node's linkedlist

	node *n = new node(other_node->coefficient, other_node->exponent);  // this is the node to insert
	
	if (!this_node) {
		// insert here (at end of linkedlist)
		this_node = n;
		this->tail = this_node;
	} else if (this_node->exponent== other_node->exponent) {
		// add coefficients
		this_node->coefficient += other_node->coefficient;
	} else if (this_node->next && this_node->next->exponent > other_node->exponent) {
		if (this_node->exponent < other_node->exponent) {
			// insert after this_node
			node *tmp = this_node->next;
			this_node->next = n;
			n->next = tmp;
		} else { // this means that need to insert at beginning of linkedlist
			node *tmp = this_node;
			head = n;
			n->next = tmp;
		}
	} else this->addPoly_helper(this_node->next, other_node);  // this means this_node->exponent < other_node->exponent
}

linkedlist_poly linkedlist_poly::addPoly(linkedlist_poly const &other) {
// PRECONDITION: this linkedlist != empty && other != empty
// POSTCONDITION: returns linkedlist_poly object that is this linkedlist_poly + other

	linkedlist_poly lp3;
	node *n = head;  // make lp3 a copy of *this
	while (n) {
		lp3.insert_end(n->coefficient, n->exponent);	
		n = n->next;
	}

	cout << "lp3 (copy of lp1): " << lp3.writePoly() << endl;

	node *other_node = other.head;
	while (other_node) {  // loop through other's linkedlsit
		lp3.addPoly_helper(lp3.head, other_node);  // add each node in other to lp3
		other_node = other_node->next;
	}
	return lp3;
}

linkedlist_poly linkedlist_poly::mulPoly(linkedlist_poly const &other) {
	return linkedlist_poly();
}

linkedlist_poly linkedlist_poly::squPoly() {
	return linkedlist_poly();
}

// -----------------------------------------------------------------
// PUBLIC HELPER METHODS

void linkedlist_poly::insert_end(int coef, int exp) {
	node *n = new node(coef,exp);
	if (!head)
		head = n;
	else
		tail->next = n;
	n->next = nullptr;
	tail = n;
}

// -----------------------------------------------------------------
// PRIVATE HELPER FUNCTIONS

pair<int,int> linkedlist_poly::readNumber(string input, int i) {
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

void linkedlist_poly::readPoly(string str_poly) {
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
				// if (i<str_poly.length()-1 && exponent>size) throw outOfOrderPoly();
				insert_end(coefficient,exponent);
				read_coefficient_next=true;
			}
		} else i++;
	}
	if (!read_coefficient_next) throw invalidPolynomial();
		// this means coefficient was last term (each coefficient inputted must have a exponent)
}
