#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include "variable.h"

class Parser{
public:
	void parse(std::string);
	Variable* findVar(std::string varName) const;
	void addVar(Variable* var);
	void printVars() const;
	~Parser();
private:
	std::vector<Variable*> varList;
	void evaluate();
};


#endif //PARSER_H
