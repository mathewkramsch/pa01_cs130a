// ll.h
// linkedlist representation of a sparse polynomial

#ifndef LL_H
#define LL_H
#include "string"

class linkedlist_poly {
	public:
		// CONSTTRUCTORS/DESTRUCTOR
		linkedlist_poly(): size(0), head(0), tail(0) {}
		linkedlist_poly(std::string str_poly);
		// linkedlist_poly(int size1, node *head);
		linkedlist_poly& operator =(const linkedlist_poly &right);
		~linkedlist_poly();

		// GETTERS
		int getSize() const { return size; }

		// PUBLIC METHODS
		std::string writePoly();  // linkedlist polynomial -> string representation
		linkedlist_poly addPoly(linkedlist_poly const &other);  // adds this poly w/ other -> = 3rd poly
		linkedlist_poly mulPoly(linkedlist_poly const &other);  // multiplies this poly w/ other -> = 3rd poly
		linkedlist_poly squPoly();  // squares this poly -> = 3rd poly

		// PUBLIC HELPER METHODS
		void insert_end(int coef, int exp);
	private:
		// PRIVATE VARIABLES
		int size;  // size of linkedlist
		struct node {
			node(int c=0, int e=0): coefficient(c), exponent(e), next(0) {}
			int coefficient;
			int exponent;
			node *next;
		};
		node *head;  // first node: 1st coeffient/exponent pair
		node *tail;  // last node

		// HELPER FUNCTIONS
		void readPoly(std::string str_poly);  // translates str_poly string to linkedlist_poly, helper for constructor
		std::pair<int,int> readNumber(std::string input, int i);  // helper function for readPoly

		void addPoly_helper(node *this_node, node *other_node);
};

#endif
