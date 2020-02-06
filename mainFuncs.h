// mainFuncs.h

#ifndef MAINFUNCS_H
#define MAINFUNCS_H
#include <utility>
#include <vector>
#include "string"

// EXCEPTION CLASSES
class noInput { public: void mssg(); };
class invalidOperator { public: void mssg(); };
class invalidPolynomial { public: void mssg(); };
class invalidOperation {public: void mssg(); };

// MAIN HELPER FUNCTIONS
char get_operation(std::string input);
std::pair<std::vector<int>,std::vector<int>> vectorize_input(std::string input);
std::pair<int,int> read_number(std::string input, int i);

// DEBUGGING
void print_vector(std::vector<int> v, int num);

#endif
