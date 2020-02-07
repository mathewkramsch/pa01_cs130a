// mainFuncs.h

#ifndef MAINFUNCS_H
#define MAINFUNCS_H
#include <utility>
#include <vector>
#include "string"

// MAIN HELPER FUNCTIONS
char get_operation(std::string input);
std::pair<std::string,std::string> parse_input(std::string input);
	// std::pair<std::vector<int>,std::vector<int>> vectorize_input(std::string input);
// std::pair<int,int> read_number(std::string input, int i);

// DEBUGGING
void print_vector(std::vector<int> v, int num);

#endif
