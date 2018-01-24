#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include "variable.h"

class Parser{
public:
	void parse(std::string);
private:
	std::vector<Variable*> varList;
	void evaluate();
};


#endif //PARSER_H
