// mainFuncs.h

#ifndef MAINFUNCS_H
#define MAINFUNCS_H
#include <utility>
#include "string"

// MAIN HELPER FUNCTIONS
char get_operation(std::string input);  // gets operation from command-line input
std::pair<std::string,std::string> parse_input(std::string input);  // splits input into a string for each polynomial

#endif
