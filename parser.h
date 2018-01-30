#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include "variable.h"
#include "matrix.h"

class Parser{
public:
	void parse(std::string);
	Variable* findVar(std::string varName) const;
	void addVar(Variable* var);
	void printVars() const;
	~Parser();
private:
	std::vector<Variable*> varList;
	std::string find_op(std::string s,char c);
	std::string find_brackets (std::string s);
	std::string removeSpaces(std::string input);
	std::string solve_trig (std::string s);
	std::string find_inside (int pos , std::string s);
	void matrixName(std::string path);
	Matrix findMatrix (char c, std::string path);
};


#endif //PARSER_H
