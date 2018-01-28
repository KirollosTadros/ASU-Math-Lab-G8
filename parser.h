#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include "variable.h"
#include <string>
#include "matrix.h""
using namespace std;
class Parser{
public:
	void parse(std::string);
	Variable* findVar(std::string varName) const;
	void addVar(Variable* var);
	void printVars() const;
	~Parser();
private:
	vector<Variable*> varList;
	void evaluate();
	string find_op(string s,char c);
string find_brackets (string s);
string removeSpaces(string input);
string solve_trig (string s);
string find_inside (int pos , string s);
void matrixName(string path);
Matrix findMatrix (char c, string path);
};


#endif //PARSER_H
